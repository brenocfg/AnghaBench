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
typedef  int /*<<< orphan*/  uint32_t ;
struct bnxt_softc {int /*<<< orphan*/  dev; } ;
struct bnxt_bar_info {int /*<<< orphan*/ * res; int /*<<< orphan*/  size; int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnxt_map_bar(struct bnxt_softc *softc, struct bnxt_bar_info *bar, int bar_num, bool shareable)
{
	uint32_t	flag;

	if (bar->res != NULL) {
		device_printf(softc->dev, "Bar %d already mapped\n", bar_num);
		return EDOOFUS;
	}

	bar->rid = PCIR_BAR(bar_num);
	flag = RF_ACTIVE;
	if (shareable)
		flag |= RF_SHAREABLE;

	if ((bar->res =
		bus_alloc_resource_any(softc->dev,
			   SYS_RES_MEMORY,
			   &bar->rid,
			   flag)) == NULL) {
		device_printf(softc->dev,
		    "PCI BAR%d mapping failure\n", bar_num);
		return (ENXIO);
	}
	bar->tag = rman_get_bustag(bar->res);
	bar->handle = rman_get_bushandle(bar->res);
	bar->size = rman_get_size(bar->res);

	return 0;
}