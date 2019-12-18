#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
struct TYPE_11__ {TYPE_2__* tn_aobj; } ;
struct tmpfs_node {int tn_size; TYPE_1__ tn_reg; } ;
struct tmpfs_mount {int /*<<< orphan*/  tm_pages_used; } ;
typedef  int off_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_12__ {scalar_t__ size; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 struct tmpfs_mount* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VM_PAGER_OK ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ VREG ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pmap_zero_page_area (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  swap_pager_freespace (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ tmpfs_pages_check_avail (struct tmpfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_page_remove (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vm_page_all_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_alloc (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_grab (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_launder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 
 int vm_pager_get_pages (TYPE_2__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_pager_has_page (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_page_unswapped (int /*<<< orphan*/ *) ; 

int
tmpfs_reg_resize(struct vnode *vp, off_t newsize, boolean_t ignerr)
{
	struct tmpfs_mount *tmp;
	struct tmpfs_node *node;
	vm_object_t uobj;
	vm_page_t m;
	vm_pindex_t idx, newpages, oldpages;
	off_t oldsize;
	int base, rv;

	MPASS(vp->v_type == VREG);
	MPASS(newsize >= 0);

	node = VP_TO_TMPFS_NODE(vp);
	uobj = node->tn_reg.tn_aobj;
	tmp = VFS_TO_TMPFS(vp->v_mount);

	/*
	 * Convert the old and new sizes to the number of pages needed to
	 * store them.  It may happen that we do not need to do anything
	 * because the last allocated page can accommodate the change on
	 * its own.
	 */
	oldsize = node->tn_size;
	oldpages = OFF_TO_IDX(oldsize + PAGE_MASK);
	MPASS(oldpages == uobj->size);
	newpages = OFF_TO_IDX(newsize + PAGE_MASK);

	if (__predict_true(newpages == oldpages && newsize >= oldsize)) {
		node->tn_size = newsize;
		return (0);
	}

	if (newpages > oldpages &&
	    tmpfs_pages_check_avail(tmp, newpages - oldpages) == 0)
		return (ENOSPC);

	VM_OBJECT_WLOCK(uobj);
	if (newsize < oldsize) {
		/*
		 * Zero the truncated part of the last page.
		 */
		base = newsize & PAGE_MASK;
		if (base != 0) {
			idx = OFF_TO_IDX(newsize);
retry:
			m = vm_page_grab(uobj, idx, VM_ALLOC_NOCREAT);
			if (m != NULL) {
				MPASS(vm_page_all_valid(m));
			} else if (vm_pager_has_page(uobj, idx, NULL, NULL)) {
				m = vm_page_alloc(uobj, idx, VM_ALLOC_NORMAL |
				    VM_ALLOC_WAITFAIL);
				if (m == NULL)
					goto retry;
				rv = vm_pager_get_pages(uobj, &m, 1, NULL,
				    NULL);
				if (rv == VM_PAGER_OK) {
					/*
					 * Since the page was not resident,
					 * and therefore not recently
					 * accessed, immediately enqueue it
					 * for asynchronous laundering.  The
					 * current operation is not regarded
					 * as an access.
					 */
					vm_page_lock(m);
					vm_page_launder(m);
					vm_page_unlock(m);
				} else {
					vm_page_free(m);
					if (ignerr)
						m = NULL;
					else {
						VM_OBJECT_WUNLOCK(uobj);
						return (EIO);
					}
				}
			}
			if (m != NULL) {
				pmap_zero_page_area(m, base, PAGE_SIZE - base);
				vm_page_dirty(m);
				vm_page_xunbusy(m);
				vm_pager_page_unswapped(m);
			}
		}

		/*
		 * Release any swap space and free any whole pages.
		 */
		if (newpages < oldpages) {
			swap_pager_freespace(uobj, newpages, oldpages -
			    newpages);
			vm_object_page_remove(uobj, newpages, 0, 0);
		}
	}
	uobj->size = newpages;
	VM_OBJECT_WUNLOCK(uobj);

	atomic_add_long(&tmp->tm_pages_used, newpages - oldpages);

	node->tn_size = newsize;
	return (0);
}