#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * bo_object; } ;
struct vnode {int v_iflag; TYPE_1__ v_bufobj; } ;
struct thread {int dummy; } ;
struct smbnode {int n_flag; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int NFLUSHINPROG ; 
 int NFLUSHWANT ; 
 int NMODIFIED ; 
 int /*<<< orphan*/  OBJPC_SYNC ; 
 int /*<<< orphan*/  PCATCH ; 
 scalar_t__ PRIBIO ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int hz ; 
 int smb_td_intr (struct thread*) ; 
 int tsleep (int*,scalar_t__,char*,int) ; 
 int vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_page_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

int
smbfs_vinvalbuf(struct vnode *vp, struct thread *td)
{
	struct smbnode *np = VTOSMB(vp);
	int error = 0;

	if (vp->v_iflag & VI_DOOMED)
		return 0;

	while (np->n_flag & NFLUSHINPROG) {
		np->n_flag |= NFLUSHWANT;
		error = tsleep(&np->n_flag, PRIBIO + 2, "smfsvinv", 2 * hz);
		error = smb_td_intr(td);
		if (error == EINTR)
			return EINTR;
	}
	np->n_flag |= NFLUSHINPROG;

	if (vp->v_bufobj.bo_object != NULL) {
		VM_OBJECT_WLOCK(vp->v_bufobj.bo_object);
		vm_object_page_clean(vp->v_bufobj.bo_object, 0, 0, OBJPC_SYNC);
		VM_OBJECT_WUNLOCK(vp->v_bufobj.bo_object);
	}

	error = vinvalbuf(vp, V_SAVE, PCATCH, 0);
	while (error) {
		if (error == ERESTART || error == EINTR) {
			np->n_flag &= ~NFLUSHINPROG;
			if (np->n_flag & NFLUSHWANT) {
				np->n_flag &= ~NFLUSHWANT;
				wakeup(&np->n_flag);
			}
			return EINTR;
		}
		error = vinvalbuf(vp, V_SAVE, PCATCH, 0);
	}
	np->n_flag &= ~(NMODIFIED | NFLUSHINPROG);
	if (np->n_flag & NFLUSHWANT) {
		np->n_flag &= ~NFLUSHWANT;
		wakeup(&np->n_flag);
	}
	return (error);
}