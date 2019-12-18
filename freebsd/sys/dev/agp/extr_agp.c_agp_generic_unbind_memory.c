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
struct agp_softc {int /*<<< orphan*/  as_lock; } ;
struct agp_memory {int am_size; scalar_t__ am_is_bound; scalar_t__ am_offset; int /*<<< orphan*/  am_obj; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_PAGE_SIZE ; 
 int /*<<< orphan*/  AGP_UNBIND_PAGE (int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atop (int) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
agp_generic_unbind_memory(device_t dev, struct agp_memory *mem)
{
	struct agp_softc *sc = device_get_softc(dev);
	vm_page_t m;
	int i;

	mtx_lock(&sc->as_lock);

	if (!mem->am_is_bound) {
		device_printf(dev, "memory is not bound\n");
		mtx_unlock(&sc->as_lock);
		return EINVAL;
	}


	/*
	 * Unbind the individual pages and flush the chipset's
	 * TLB. Unwire the pages so they can be swapped.
	 */
	for (i = 0; i < mem->am_size; i += AGP_PAGE_SIZE)
		AGP_UNBIND_PAGE(dev, mem->am_offset + i);

	AGP_FLUSH_TLB(dev);

	VM_OBJECT_WLOCK(mem->am_obj);
	for (i = 0; i < mem->am_size; i += PAGE_SIZE) {
		m = vm_page_lookup(mem->am_obj, atop(i));
		vm_page_unwire(m, PQ_INACTIVE);
	}
	VM_OBJECT_WUNLOCK(mem->am_obj);

	mem->am_offset = 0;
	mem->am_is_bound = 0;

	mtx_unlock(&sc->as_lock);

	return 0;
}