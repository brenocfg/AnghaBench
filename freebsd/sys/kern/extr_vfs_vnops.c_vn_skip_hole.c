#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIOSEEKDATA ; 
 int /*<<< orphan*/  FIOSEEKHOLE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int VOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 

__attribute__((used)) static off_t
vn_skip_hole(struct vnode *outvp, off_t xfer2, off_t *outoffp, off_t *xferp,
    off_t *dataoffp, off_t *holeoffp, struct ucred *cred)
{
	int error;
	off_t delta;

	if (*holeoffp == 0 || *holeoffp <= *outoffp) {
		*dataoffp = *outoffp;
		error = VOP_IOCTL(outvp, FIOSEEKDATA, dataoffp, 0, cred,
		    curthread);
		if (error == 0) {
			*holeoffp = *dataoffp;
			error = VOP_IOCTL(outvp, FIOSEEKHOLE, holeoffp, 0, cred,
			    curthread);
		}
		if (error != 0 || *holeoffp == *dataoffp) {
			/*
			 * Since outvp is unlocked, it may be possible for
			 * another thread to do a truncate(), lseek(), write()
			 * creating a hole at startoff between the above
			 * VOP_IOCTL() calls, if the other thread does not do
			 * rangelocking.
			 * If that happens, *holeoffp == *dataoffp and finding
			 * the hole has failed, so disable vn_skip_hole().
			 */
			*holeoffp = -1;	/* Disable use of vn_skip_hole(). */
			return (xfer2);
		}
		KASSERT(*dataoffp >= *outoffp,
		    ("vn_skip_hole: dataoff=%jd < outoff=%jd",
		    (intmax_t)*dataoffp, (intmax_t)*outoffp));
		KASSERT(*holeoffp > *dataoffp,
		    ("vn_skip_hole: holeoff=%jd <= dataoff=%jd",
		    (intmax_t)*holeoffp, (intmax_t)*dataoffp));
	}

	/*
	 * If there is a hole before the data starts, advance *outoffp and
	 * *xferp past the hole.
	 */
	if (*dataoffp > *outoffp) {
		delta = *dataoffp - *outoffp;
		if (delta >= *xferp) {
			/* Entire *xferp is a hole. */
			*outoffp += *xferp;
			*xferp = 0;
			return (0);
		}
		*xferp -= delta;
		*outoffp += delta;
		xfer2 = MIN(xfer2, *xferp);
	}

	/*
	 * If a hole starts before the end of this xfer2, reduce this xfer2 so
	 * that the write ends at the start of the hole.
	 * *holeoffp should always be greater than *outoffp, but for the
	 * non-INVARIANTS case, check this to make sure xfer2 remains a sane
	 * value.
	 */
	if (*holeoffp > *outoffp && *holeoffp < *outoffp + xfer2)
		xfer2 = *holeoffp - *outoffp;
	return (xfer2);
}