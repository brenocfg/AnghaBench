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
struct isci_softc {int num_interrupts; int /*<<< orphan*/  device; int /*<<< orphan*/ * handlers; struct ISCI_INTERRUPT_INFO* interrupt_info; } ;
struct ISCI_INTERRUPT_INFO {int /*<<< orphan*/ * tag; int /*<<< orphan*/ * res; scalar_t__ rid; void* interrupt_target_handle; int /*<<< orphan*/ * handlers; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SCIC_LEGACY_LINE_INTERRUPT_TYPE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ISCI_INTERRUPT_INFO*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isci_interrupt_legacy_handler ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  scic_controller_get_handler_methods (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isci_interrupt_setup_legacy(struct isci_softc *isci)
{
	struct ISCI_INTERRUPT_INFO *interrupt_info = &isci->interrupt_info[0];

	isci->num_interrupts = 1;

	scic_controller_get_handler_methods(SCIC_LEGACY_LINE_INTERRUPT_TYPE,
	    0, &isci->handlers[0]);

	interrupt_info->handlers = &isci->handlers[0];
	interrupt_info->rid = 0;
	interrupt_info->interrupt_target_handle = (void *)isci;

	interrupt_info->res = bus_alloc_resource_any(isci->device, SYS_RES_IRQ,
	    &interrupt_info->rid, RF_SHAREABLE|RF_ACTIVE);

	if (interrupt_info->res == NULL) {
		isci_log_message(0, "ISCI", "bus_alloc_resource failed\n");
		return (-1);
	}

	interrupt_info->tag = NULL;
	if (bus_setup_intr(isci->device, interrupt_info->res,
	    INTR_TYPE_CAM | INTR_MPSAFE, NULL, isci_interrupt_legacy_handler,
	    interrupt_info, &interrupt_info->tag)) {
		isci_log_message(0, "ISCI", "bus_setup_intr failed\n");
		return (-1);
	}

	return (0);
}