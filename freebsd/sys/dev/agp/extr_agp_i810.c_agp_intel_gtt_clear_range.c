#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct agp_i810_softc {TYPE_2__* match; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_gtt_pte ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* install_gtt_pte ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bogus_page ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

void
agp_intel_gtt_clear_range(device_t dev, u_int first_entry, u_int num_entries)
{
	struct agp_i810_softc *sc;
	u_int i;

	sc = device_get_softc(dev);
	for (i = 0; i < num_entries; i++)
		sc->match->driver->install_gtt_pte(dev, first_entry + i,
		    VM_PAGE_TO_PHYS(bogus_page), 0);
	sc->match->driver->read_gtt_pte(dev, first_entry + num_entries - 1);
}