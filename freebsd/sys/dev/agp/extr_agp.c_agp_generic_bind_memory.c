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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
typedef  int uintmax_t ;
struct agp_softc {int /*<<< orphan*/  as_lock; } ;
struct agp_memory {int am_size; int am_is_bound; int am_offset; int /*<<< orphan*/  am_obj; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_BIND_PAGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AGP_DPF (char*,int,...) ; 
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 int AGP_PAGE_SIZE ; 
 int /*<<< orphan*/  AGP_UNBIND_PAGE (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OFF_TO_IDX (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ ) ; 

int
agp_generic_bind_memory(device_t dev, struct agp_memory *mem,
			vm_offset_t offset)
{
	struct agp_softc *sc = device_get_softc(dev);
	vm_offset_t i, j, k;
	vm_page_t m;
	int error;

	/* Do some sanity checks first. */
	if ((offset & (AGP_PAGE_SIZE - 1)) != 0 ||
	    offset + mem->am_size > AGP_GET_APERTURE(dev)) {
		device_printf(dev, "binding memory at bad offset %#x\n",
		    (int)offset);
		return EINVAL;
	}

	/*
	 * Allocate the pages early, before acquiring the lock,
	 * because vm_page_grab() may sleep and we can't hold a mutex
	 * while sleeping.
	 */
	VM_OBJECT_WLOCK(mem->am_obj);
	for (i = 0; i < mem->am_size; i += PAGE_SIZE) {
		/*
		 * Find a page from the object and wire it
		 * down. This page will be mapped using one or more
		 * entries in the GATT (assuming that PAGE_SIZE >=
		 * AGP_PAGE_SIZE. If this is the first call to bind,
		 * the pages will be allocated and zeroed.
		 */
		m = vm_page_grab(mem->am_obj, OFF_TO_IDX(i),
		    VM_ALLOC_WIRED | VM_ALLOC_ZERO);
		AGP_DPF("found page pa=%#jx\n", (uintmax_t)VM_PAGE_TO_PHYS(m));
	}
	VM_OBJECT_WUNLOCK(mem->am_obj);

	mtx_lock(&sc->as_lock);

	if (mem->am_is_bound) {
		device_printf(dev, "memory already bound\n");
		error = EINVAL;
		VM_OBJECT_WLOCK(mem->am_obj);
		i = 0;
		goto bad;
	}
	
	/*
	 * Bind the individual pages and flush the chipset's
	 * TLB.
	 */
	VM_OBJECT_WLOCK(mem->am_obj);
	for (i = 0; i < mem->am_size; i += PAGE_SIZE) {
		m = vm_page_lookup(mem->am_obj, OFF_TO_IDX(i));

		/*
		 * Install entries in the GATT, making sure that if
		 * AGP_PAGE_SIZE < PAGE_SIZE and mem->am_size is not
		 * aligned to PAGE_SIZE, we don't modify too many GATT 
		 * entries.
		 */
		for (j = 0; j < PAGE_SIZE && i + j < mem->am_size;
		     j += AGP_PAGE_SIZE) {
			vm_offset_t pa = VM_PAGE_TO_PHYS(m) + j;
			AGP_DPF("binding offset %#jx to pa %#jx\n",
				(uintmax_t)offset + i + j, (uintmax_t)pa);
			error = AGP_BIND_PAGE(dev, offset + i + j, pa);
			if (error) {
				/*
				 * Bail out. Reverse all the mappings
				 * and unwire the pages.
				 */
				for (k = 0; k < i + j; k += AGP_PAGE_SIZE)
					AGP_UNBIND_PAGE(dev, offset + k);
				goto bad;
			}
		}
		vm_page_xunbusy(m);
	}
	VM_OBJECT_WUNLOCK(mem->am_obj);

	/*
	 * Make sure the chipset gets the new mappings.
	 */
	AGP_FLUSH_TLB(dev);

	mem->am_offset = offset;
	mem->am_is_bound = 1;

	mtx_unlock(&sc->as_lock);

	return 0;
bad:
	mtx_unlock(&sc->as_lock);
	VM_OBJECT_ASSERT_WLOCKED(mem->am_obj);
	for (k = 0; k < mem->am_size; k += PAGE_SIZE) {
		m = vm_page_lookup(mem->am_obj, OFF_TO_IDX(k));
		if (k >= i)
			vm_page_xunbusy(m);
		vm_page_unwire(m, PQ_INACTIVE);
	}
	VM_OBJECT_WUNLOCK(mem->am_obj);

	return error;
}