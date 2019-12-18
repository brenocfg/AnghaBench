#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct vnode {scalar_t__ v_type; TYPE_2__* v_object; int /*<<< orphan*/  v_mount; } ;
struct mount {int dummy; } ;
struct TYPE_19__ {scalar_t__ type; struct vnode* handle; } ;
struct TYPE_18__ {scalar_t__ pindex; scalar_t__ dirty; TYPE_2__* object; } ;

/* Variables and functions */
 int EBUSY ; 
 int EDEADLK ; 
 int EIO ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_SHARED ; 
 int LK_TIMELOCK ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 scalar_t__ MNT_SHARED_WRITES (int /*<<< orphan*/ ) ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ vget (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_reference_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_in_laundry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_try_remove_write (TYPE_1__*) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 int vm_pageout_cluster (TYPE_1__*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 scalar_t__ vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
vm_pageout_clean(vm_page_t m, int *numpagedout)
{
	struct vnode *vp;
	struct mount *mp;
	vm_object_t object;
	vm_pindex_t pindex;
	int error, lockmode;

	vm_page_assert_locked(m);
	object = m->object;
	VM_OBJECT_ASSERT_WLOCKED(object);
	error = 0;
	vp = NULL;
	mp = NULL;

	/*
	 * The object is already known NOT to be dead.   It
	 * is possible for the vget() to block the whole
	 * pageout daemon, but the new low-memory handling
	 * code should prevent it.
	 *
	 * We can't wait forever for the vnode lock, we might
	 * deadlock due to a vn_read() getting stuck in
	 * vm_wait while holding this vnode.  We skip the 
	 * vnode if we can't get it in a reasonable amount
	 * of time.
	 */
	if (object->type == OBJT_VNODE) {
		vm_page_unlock(m);
		vm_page_xunbusy(m);
		vp = object->handle;
		if (vp->v_type == VREG &&
		    vn_start_write(vp, &mp, V_NOWAIT) != 0) {
			mp = NULL;
			error = EDEADLK;
			goto unlock_all;
		}
		KASSERT(mp != NULL,
		    ("vp %p with NULL v_mount", vp));
		vm_object_reference_locked(object);
		pindex = m->pindex;
		VM_OBJECT_WUNLOCK(object);
		lockmode = MNT_SHARED_WRITES(vp->v_mount) ?
		    LK_SHARED : LK_EXCLUSIVE;
		if (vget(vp, lockmode | LK_TIMELOCK, curthread)) {
			vp = NULL;
			error = EDEADLK;
			goto unlock_mp;
		}
		VM_OBJECT_WLOCK(object);

		/*
		 * Ensure that the object and vnode were not disassociated
		 * while locks were dropped.
		 */
		if (vp->v_object != object) {
			error = ENOENT;
			goto unlock_all;
		}
		vm_page_lock(m);

		/*
		 * While the object and page were unlocked, the page
		 * may have been:
		 * (1) moved to a different queue,
		 * (2) reallocated to a different object,
		 * (3) reallocated to a different offset, or
		 * (4) cleaned.
		 */
		if (!vm_page_in_laundry(m) || m->object != object ||
		    m->pindex != pindex || m->dirty == 0) {
			vm_page_unlock(m);
			error = ENXIO;
			goto unlock_all;
		}

		/*
		 * The page may have been busied while the object and page
		 * locks were released.
		 */
		if (vm_page_tryxbusy(m) == 0) {
			vm_page_unlock(m);
			error = EBUSY;
			goto unlock_all;
		}
	}

	/*
	 * Remove all writeable mappings, failing if the page is wired.
	 */
	if (!vm_page_try_remove_write(m)) {
		vm_page_xunbusy(m);
		vm_page_unlock(m);
		error = EBUSY;
		goto unlock_all;
	}
	vm_page_unlock(m);

	/*
	 * If a page is dirty, then it is either being washed
	 * (but not yet cleaned) or it is still in the
	 * laundry.  If it is still in the laundry, then we
	 * start the cleaning operation. 
	 */
	if ((*numpagedout = vm_pageout_cluster(m)) == 0)
		error = EIO;

unlock_all:
	VM_OBJECT_WUNLOCK(object);

unlock_mp:
	vm_page_lock_assert(m, MA_NOTOWNED);
	if (mp != NULL) {
		if (vp != NULL)
			vput(vp);
		vm_object_deallocate(object);
		vn_finished_write(mp);
	}

	return (error);
}