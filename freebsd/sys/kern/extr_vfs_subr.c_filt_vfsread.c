#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; } ;
struct vattr {scalar_t__ va_size; } ;
struct knote {int kn_flags; scalar_t__ kn_data; int kn_sfflags; TYPE_1__* kn_fp; scalar_t__ kn_hook; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_3__ {scalar_t__ f_offset; } ;

/* Variables and functions */
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int NOTE_FILE_POLL ; 
 long NOTE_REVOKE ; 
 scalar_t__ VBAD ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 

__attribute__((used)) static int
filt_vfsread(struct knote *kn, long hint)
{
	struct vnode *vp = (struct vnode *)kn->kn_hook;
	struct vattr va;
	int res;

	/*
	 * filesystem is gone, so set the EOF flag and schedule
	 * the knote for deletion.
	 */
	if (hint == NOTE_REVOKE || (hint == 0 && vp->v_type == VBAD)) {
		VI_LOCK(vp);
		kn->kn_flags |= (EV_EOF | EV_ONESHOT);
		VI_UNLOCK(vp);
		return (1);
	}

	if (VOP_GETATTR(vp, &va, curthread->td_ucred))
		return (0);

	VI_LOCK(vp);
	kn->kn_data = va.va_size - kn->kn_fp->f_offset;
	res = (kn->kn_sfflags & NOTE_FILE_POLL) != 0 || kn->kn_data != 0;
	VI_UNLOCK(vp);
	return (res);
}