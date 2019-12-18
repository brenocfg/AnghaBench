#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct mount {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_SHARED ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MNT_SHARED_WRITES (struct mount*) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  bwillwrite () ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ vn_skip_hole (struct vnode*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,struct ucred*) ; 
 int vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int vn_truncate_locked (struct vnode*,scalar_t__,int,struct ucred*) ; 

__attribute__((used)) static int
vn_write_outvp(struct vnode *outvp, char *dat, off_t outoff, off_t xfer,
    u_long blksize, bool growfile, bool checkhole, struct ucred *cred)
{
	struct mount *mp;
	off_t dataoff, holeoff, xfer2;
	int error, lckf;

	/*
	 * Loop around doing writes of blksize until write has been completed.
	 * Lock/unlock on each loop iteration so that a bwillwrite() can be
	 * done for each iteration, since the xfer argument can be very
	 * large if there is a large hole to punch in the output file.
	 */
	error = 0;
	holeoff = 0;
	do {
		xfer2 = MIN(xfer, blksize);
		if (checkhole) {
			/*
			 * Punching a hole.  Skip writing if there is
			 * already a hole in the output file.
			 */
			xfer2 = vn_skip_hole(outvp, xfer2, &outoff, &xfer,
			    &dataoff, &holeoff, cred);
			if (xfer == 0)
				break;
			if (holeoff < 0)
				checkhole = false;
			KASSERT(xfer2 > 0, ("vn_write_outvp: xfer2=%jd",
			    (intmax_t)xfer2));
		}
		bwillwrite();
		mp = NULL;
		error = vn_start_write(outvp, &mp, V_WAIT);
		if (error == 0) {
			if (MNT_SHARED_WRITES(mp))
				lckf = LK_SHARED;
			else
				lckf = LK_EXCLUSIVE;
			error = vn_lock(outvp, lckf);
		}
		if (error == 0) {
			if (growfile)
				error = vn_truncate_locked(outvp, outoff + xfer,
				    false, cred);
			else {
				error = vn_rdwr(UIO_WRITE, outvp, dat, xfer2,
				    outoff, UIO_SYSSPACE, IO_NODELOCKED,
				    curthread->td_ucred, cred, NULL, curthread);
				outoff += xfer2;
				xfer -= xfer2;
			}
			VOP_UNLOCK(outvp, 0);
		}
		if (mp != NULL)
			vn_finished_write(mp);
	} while (!growfile && xfer > 0 && error == 0);
	return (error);
}