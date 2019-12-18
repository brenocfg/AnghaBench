#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_1__* vm_object_t ;
struct shmfd {int shm_size; int shm_seals; scalar_t__ shm_kmappings; int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_mtime; TYPE_1__* shm_object; } ;
typedef  int off_t ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ type; int /*<<< orphan*/  charge; int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int F_SEAL_GROW ; 
 int F_SEAL_SHRINK ; 
 scalar_t__ IDX_TO_OFF (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int VM_PAGER_OK ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_zero_page_area (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  rangelock_cookie_assert (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_timestamp_lock ; 
 int /*<<< orphan*/  swap_pager_freespace (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  swap_release_by_cred (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_reserve_by_cred (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_page_remove (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int vm_page_all_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_alloc (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_grab (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_launder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 
 int vm_pager_get_pages (TYPE_1__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_pager_has_page (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_page_unswapped (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
shm_dotruncate_locked(struct shmfd *shmfd, off_t length, void *rl_cookie)
{
	vm_object_t object;
	vm_page_t m;
	vm_pindex_t idx, nobjsize;
	vm_ooffset_t delta;
	int base, rv;

	KASSERT(length >= 0, ("shm_dotruncate: length < 0"));
	object = shmfd->shm_object;
	VM_OBJECT_ASSERT_WLOCKED(object);
	rangelock_cookie_assert(rl_cookie, RA_WLOCKED);
	if (length == shmfd->shm_size)
		return (0);
	nobjsize = OFF_TO_IDX(length + PAGE_MASK);

	/* Are we shrinking?  If so, trim the end. */
	if (length < shmfd->shm_size) {
		if ((shmfd->shm_seals & F_SEAL_SHRINK) != 0)
			return (EPERM);

		/*
		 * Disallow any requests to shrink the size if this
		 * object is mapped into the kernel.
		 */
		if (shmfd->shm_kmappings > 0)
			return (EBUSY);

		/*
		 * Zero the truncated part of the last page.
		 */
		base = length & PAGE_MASK;
		if (base != 0) {
			idx = OFF_TO_IDX(length);
retry:
			m = vm_page_grab(object, idx, VM_ALLOC_NOCREAT);
			if (m != NULL) {
				MPASS(vm_page_all_valid(m));
			} else if (vm_pager_has_page(object, idx, NULL, NULL)) {
				m = vm_page_alloc(object, idx,
				    VM_ALLOC_NORMAL | VM_ALLOC_WAITFAIL);
				if (m == NULL)
					goto retry;
				rv = vm_pager_get_pages(object, &m, 1, NULL,
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
					vm_page_launder(m);
				} else {
					vm_page_free(m);
					VM_OBJECT_WUNLOCK(object);
					return (EIO);
				}
			}
			if (m != NULL) {
				pmap_zero_page_area(m, base, PAGE_SIZE - base);
				KASSERT(vm_page_all_valid(m),
				    ("shm_dotruncate: page %p is invalid", m));
				vm_page_dirty(m);
				vm_page_xunbusy(m);
				vm_pager_page_unswapped(m);
			}
		}
		delta = IDX_TO_OFF(object->size - nobjsize);

		/* Toss in memory pages. */
		if (nobjsize < object->size)
			vm_object_page_remove(object, nobjsize, object->size,
			    0);

		/* Toss pages from swap. */
		if (object->type == OBJT_SWAP)
			swap_pager_freespace(object, nobjsize, delta);

		/* Free the swap accounted for shm */
		swap_release_by_cred(delta, object->cred);
		object->charge -= delta;
	} else {
		if ((shmfd->shm_seals & F_SEAL_GROW) != 0)
			return (EPERM);

		/* Try to reserve additional swap space. */
		delta = IDX_TO_OFF(nobjsize - object->size);
		if (!swap_reserve_by_cred(delta, object->cred))
			return (ENOMEM);
		object->charge += delta;
	}
	shmfd->shm_size = length;
	mtx_lock(&shm_timestamp_lock);
	vfs_timestamp(&shmfd->shm_ctime);
	shmfd->shm_mtime = shmfd->shm_ctime;
	mtx_unlock(&shm_timestamp_lock);
	object->size = nobjsize;
	return (0);
}