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
struct TYPE_2__ {scalar_t__ bv_cnt; } ;
struct bufobj {scalar_t__ bo_numoutput; TYPE_1__ bo_dirty; TYPE_1__ bo_clean; int /*<<< orphan*/ * bo_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int BO_SYNC (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  OBJPR_CLEANONLY ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int V_ALLOWCLEAN ; 
 int V_ALT ; 
 int V_CLEANONLY ; 
 int V_NORMAL ; 
 int V_SAVE ; 
 int V_VMIO ; 
 int bufobj_wwait (struct bufobj*,int,int) ; 
 int flushbuflist (TYPE_1__*,int,struct bufobj*,int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vm_object_page_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pip_wait_unlocked (int /*<<< orphan*/ *,char*) ; 

int
bufobj_invalbuf(struct bufobj *bo, int flags, int slpflag, int slptimeo)
{
	int error;

	BO_LOCK(bo);
	if (flags & V_SAVE) {
		error = bufobj_wwait(bo, slpflag, slptimeo);
		if (error) {
			BO_UNLOCK(bo);
			return (error);
		}
		if (bo->bo_dirty.bv_cnt > 0) {
			BO_UNLOCK(bo);
			if ((error = BO_SYNC(bo, MNT_WAIT)) != 0)
				return (error);
			/*
			 * XXX We could save a lock/unlock if this was only
			 * enabled under INVARIANTS
			 */
			BO_LOCK(bo);
			if (bo->bo_numoutput > 0 || bo->bo_dirty.bv_cnt > 0)
				panic("vinvalbuf: dirty bufs");
		}
	}
	/*
	 * If you alter this loop please notice that interlock is dropped and
	 * reacquired in flushbuflist.  Special care is needed to ensure that
	 * no race conditions occur from this.
	 */
	do {
		error = flushbuflist(&bo->bo_clean,
		    flags, bo, slpflag, slptimeo);
		if (error == 0 && !(flags & V_CLEANONLY))
			error = flushbuflist(&bo->bo_dirty,
			    flags, bo, slpflag, slptimeo);
		if (error != 0 && error != EAGAIN) {
			BO_UNLOCK(bo);
			return (error);
		}
	} while (error != 0);

	/*
	 * Wait for I/O to complete.  XXX needs cleaning up.  The vnode can
	 * have write I/O in-progress but if there is a VM object then the
	 * VM object can also have read-I/O in-progress.
	 */
	do {
		bufobj_wwait(bo, 0, 0);
		if ((flags & V_VMIO) == 0 && bo->bo_object != NULL) {
			BO_UNLOCK(bo);
			vm_object_pip_wait_unlocked(bo->bo_object, "bovlbx");
			BO_LOCK(bo);
		}
	} while (bo->bo_numoutput > 0);
	BO_UNLOCK(bo);

	/*
	 * Destroy the copy in the VM cache, too.
	 */
	if (bo->bo_object != NULL &&
	    (flags & (V_ALT | V_NORMAL | V_CLEANONLY | V_VMIO)) == 0) {
		VM_OBJECT_WLOCK(bo->bo_object);
		vm_object_page_remove(bo->bo_object, 0, 0, (flags & V_SAVE) ?
		    OBJPR_CLEANONLY : 0);
		VM_OBJECT_WUNLOCK(bo->bo_object);
	}

#ifdef INVARIANTS
	BO_LOCK(bo);
	if ((flags & (V_ALT | V_NORMAL | V_CLEANONLY | V_VMIO |
	    V_ALLOWCLEAN)) == 0 && (bo->bo_dirty.bv_cnt > 0 ||
	    bo->bo_clean.bv_cnt > 0))
		panic("vinvalbuf: flush failed");
	if ((flags & (V_ALT | V_NORMAL | V_CLEANONLY | V_VMIO)) == 0 &&
	    bo->bo_dirty.bv_cnt > 0)
		panic("vinvalbuf: flush dirty failed");
	BO_UNLOCK(bo);
#endif
	return (0);
}