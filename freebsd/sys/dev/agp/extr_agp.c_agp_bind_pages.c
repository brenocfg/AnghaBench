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
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
typedef  int uintmax_t ;
struct agp_softc {int /*<<< orphan*/  as_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_BIND_PAGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AGP_DPF (char*,int,int) ; 
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 int AGP_PAGE_SIZE ; 
 int /*<<< orphan*/  AGP_UNBIND_PAGE (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t OFF_TO_IDX (int) ; 
 int PAGE_SIZE ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_wired (int /*<<< orphan*/ ) ; 

int
agp_bind_pages(device_t dev, vm_page_t *pages, vm_size_t size,
    vm_offset_t offset)
{
	struct agp_softc *sc;
	vm_offset_t i, j, k, pa;
	vm_page_t m;
	int error;

	if ((size & (AGP_PAGE_SIZE - 1)) != 0 ||
	    (offset & (AGP_PAGE_SIZE - 1)) != 0)
		return (EINVAL);

	sc = device_get_softc(dev);

	mtx_lock(&sc->as_lock);
	for (i = 0; i < size; i += PAGE_SIZE) {
		m = pages[OFF_TO_IDX(i)];
		KASSERT(vm_page_wired(m),
		    ("agp_bind_pages: page %p hasn't been wired", m));

		/*
		 * Install entries in the GATT, making sure that if
		 * AGP_PAGE_SIZE < PAGE_SIZE and size is not
		 * aligned to PAGE_SIZE, we don't modify too many GATT 
		 * entries.
		 */
		for (j = 0; j < PAGE_SIZE && i + j < size; j += AGP_PAGE_SIZE) {
			pa = VM_PAGE_TO_PHYS(m) + j;
			AGP_DPF("binding offset %#jx to pa %#jx\n",
				(uintmax_t)offset + i + j, (uintmax_t)pa);
			error = AGP_BIND_PAGE(dev, offset + i + j, pa);
			if (error) {
				/*
				 * Bail out. Reverse all the mappings.
				 */
				for (k = 0; k < i + j; k += AGP_PAGE_SIZE)
					AGP_UNBIND_PAGE(dev, offset + k);

				mtx_unlock(&sc->as_lock);
				return (error);
			}
		}
	}

	AGP_FLUSH_TLB(dev);

	mtx_unlock(&sc->as_lock);
	return (0);
}