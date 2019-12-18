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
struct TYPE_6__ {int mapped; int rid; scalar_t__ irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  core_idx; } ;
struct TYPE_5__ {TYPE_1__ core_info; int /*<<< orphan*/  intr_en; } ;
struct siba_devinfo {TYPE_3__ intr; int /*<<< orphan*/  resources; TYPE_2__ core_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHND_BUS_MAP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int resource_list_add_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int
siba_register_interrupts(device_t dev, device_t child,
     struct siba_devinfo *dinfo)
{
	int error;

	/* Is backplane interrupt distribution enabled for this core? */
	if (!dinfo->core_id.intr_en)
		return (0);

	/* Have one interrupt */
	dinfo->intr.mapped = false;
	dinfo->intr.irq = 0;
	dinfo->intr.rid = -1;

	/* Map the interrupt */
	error = BHND_BUS_MAP_INTR(dev, child, 0 /* single intr is always 0 */,
	    &dinfo->intr.irq);
	if (error) {
		device_printf(dev, "failed mapping interrupt line for core %u: "
		    "%d\n", dinfo->core_id.core_info.core_idx, error);
		return (error);
	}
	dinfo->intr.mapped = true;

	/* Update the resource list */
	dinfo->intr.rid = resource_list_add_next(&dinfo->resources, SYS_RES_IRQ,
	    dinfo->intr.irq, dinfo->intr.irq, 1);

	return (0);
}