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
struct ahd_softc {TYPE_1__* platform_data; int /*<<< orphan*/  dev_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_res_type; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int ahd_map_int (struct ahd_softc*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int
ahd_pci_map_int(struct ahd_softc *ahd)
{
	int zero;

	zero = 0;
	ahd->platform_data->irq =
	    bus_alloc_resource_any(ahd->dev_softc, SYS_RES_IRQ, &zero,
				   RF_ACTIVE | RF_SHAREABLE);
	if (ahd->platform_data->irq == NULL)
		return (ENOMEM);
	ahd->platform_data->irq_res_type = SYS_RES_IRQ;
	return (ahd_map_int(ahd));
}