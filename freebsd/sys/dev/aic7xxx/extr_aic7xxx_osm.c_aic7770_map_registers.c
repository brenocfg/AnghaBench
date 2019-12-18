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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct ahc_softc {int /*<<< orphan*/  bsh; int /*<<< orphan*/  tag; TYPE_1__* platform_data; int /*<<< orphan*/  dev_softc; } ;
struct TYPE_2__ {int regs_res_id; struct resource* regs; int /*<<< orphan*/  regs_res_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

int
aic7770_map_registers(struct ahc_softc *ahc, u_int unused_ioport_arg)
{
	struct	resource *regs;
	int	rid;

	rid = 0;
	regs = bus_alloc_resource_any(ahc->dev_softc, SYS_RES_IOPORT, &rid,
				      RF_ACTIVE);
	if (regs == NULL) {
		device_printf(ahc->dev_softc, "Unable to map I/O space?!\n");
		return ENOMEM;
	}
	ahc->platform_data->regs_res_type = SYS_RES_IOPORT;
	ahc->platform_data->regs_res_id = rid;
	ahc->platform_data->regs = regs;
	ahc->tag = rman_get_bustag(regs);
	ahc->bsh = rman_get_bushandle(regs);
	return (0);
}