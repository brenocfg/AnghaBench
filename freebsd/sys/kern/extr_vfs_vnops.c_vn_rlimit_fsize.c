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
typedef  scalar_t__ uoff_t ;
struct vnode {scalar_t__ v_type; } ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_offset; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lim_cur (struct thread*,int /*<<< orphan*/ ) ; 

int
vn_rlimit_fsize(const struct vnode *vp, const struct uio *uio,
    struct thread *td)
{

	if (vp->v_type != VREG || td == NULL)
		return (0);
	if ((uoff_t)uio->uio_offset + uio->uio_resid >
	    lim_cur(td, RLIMIT_FSIZE)) {
		PROC_LOCK(td->td_proc);
		kern_psignal(td->td_proc, SIGXFSZ);
		PROC_UNLOCK(td->td_proc);
		return (EFBIG);
	}
	return (0);
}