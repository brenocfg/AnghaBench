#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int u_int ;
struct agp_i810_softc {int stolen; TYPE_2__* match; TYPE_3__* gatt; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int ag_entries; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* install_gtt_pte ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AGP_PAGE_SHIFT ; 
 int EINVAL ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i810_unbind_page(device_t dev, vm_offset_t offset)
{
	struct agp_i810_softc *sc;
	u_int index;

	sc = device_get_softc(dev);
	if (offset >= (sc->gatt->ag_entries << AGP_PAGE_SHIFT))
		return (EINVAL);
	index = offset >> AGP_PAGE_SHIFT;
	if (sc->stolen != 0 && index < sc->stolen) {
		device_printf(dev, "trying to unbind from stolen memory\n");
		return (EINVAL);
	}
	sc->match->driver->install_gtt_pte(dev, index, 0, 0);
	return (0);
}