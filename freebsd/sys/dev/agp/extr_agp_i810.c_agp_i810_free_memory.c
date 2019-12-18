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
typedef  int /*<<< orphan*/  vm_page_t ;
struct agp_memory {int am_type; scalar_t__ am_obj; int /*<<< orphan*/  am_size; scalar_t__ am_is_bound; } ;
struct TYPE_2__ {int /*<<< orphan*/  as_memory; int /*<<< orphan*/  as_allocated; } ;
struct agp_i810_softc {TYPE_1__ agp; int /*<<< orphan*/ * argb_cursor; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_PAGE_SIZE ; 
 int EBUSY ; 
 int /*<<< orphan*/  M_AGP ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct agp_memory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  am_link ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct agp_memory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i810_free_memory(device_t dev, struct agp_memory *mem)
{
	struct agp_i810_softc *sc;
	vm_page_t m;

	if (mem->am_is_bound)
		return (EBUSY);

	sc = device_get_softc(dev);

	if (mem->am_type == 2) {
		if (mem->am_size == AGP_PAGE_SIZE) {
			/*
			 * Unwire the page which we wired in alloc_memory.
			 */
			VM_OBJECT_WLOCK(mem->am_obj);
			m = vm_page_lookup(mem->am_obj, 0);
			vm_page_unwire(m, PQ_INACTIVE);
			VM_OBJECT_WUNLOCK(mem->am_obj);
		} else {
			contigfree(sc->argb_cursor, mem->am_size, M_AGP);
			sc->argb_cursor = NULL;
		}
	}

	sc->agp.as_allocated -= mem->am_size;
	TAILQ_REMOVE(&sc->agp.as_memory, mem, am_link);
	if (mem->am_obj)
		vm_object_deallocate(mem->am_obj);
	free(mem, M_AGP);
	return (0);
}