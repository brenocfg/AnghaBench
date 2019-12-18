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
struct ocs_softc {scalar_t__ n_vec; int /*<<< orphan*/  dev; int /*<<< orphan*/  tag; int /*<<< orphan*/  intr_ctx; int /*<<< orphan*/  irq; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_pci_intr ; 
 int /*<<< orphan*/ * ocs_pci_intx_filter ; 

__attribute__((used)) static int32_t
ocs_intr_setup(struct ocs_softc *ocs)
{
	driver_filter_t	*filter = NULL;

	if (0 == ocs->n_vec) {
		filter = ocs_pci_intx_filter;
	}

	if (bus_setup_intr(ocs->dev, ocs->irq, INTR_MPSAFE | INTR_TYPE_CAM,
				filter, ocs_pci_intr, &ocs->intr_ctx,
				&ocs->tag)) {
		device_printf(ocs->dev, "could not initialize interrupt\n");
		return -1;
	}

	return 0;
}