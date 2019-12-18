#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  size_t u_int ;
struct agp_i810_softc {TYPE_2__* match; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {scalar_t__ valid; scalar_t__ ref_count; } ;
struct TYPE_7__ {TYPE_1__* driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* read_gtt_pte ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  (* install_gtt_pte ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t) ; 

void
agp_intel_gtt_insert_pages(device_t dev, u_int first_entry, u_int num_entries,
    vm_page_t *pages, u_int flags)
{
	struct agp_i810_softc *sc;
	u_int i;

	sc = device_get_softc(dev);
	for (i = 0; i < num_entries; i++) {
		MPASS(pages[i]->valid == VM_PAGE_BITS_ALL);
		MPASS(pages[i]->ref_count > 0);
		sc->match->driver->install_gtt_pte(dev, first_entry + i,
		    VM_PAGE_TO_PHYS(pages[i]), flags);
	}
	sc->match->driver->read_gtt_pte(dev, first_entry + num_entries - 1);
}