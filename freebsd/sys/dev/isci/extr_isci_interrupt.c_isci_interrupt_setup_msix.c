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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
struct isci_softc {size_t controller_count; int /*<<< orphan*/  device; int /*<<< orphan*/ * controllers; int /*<<< orphan*/ * handlers; struct ISCI_INTERRUPT_INFO* interrupt_info; } ;
struct ISCI_INTERRUPT_INFO {size_t rid; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * res; int /*<<< orphan*/ * interrupt_target_handle; int /*<<< orphan*/ * handlers; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SCIC_MSIX_INTERRUPT_TYPE ; 
 size_t SCI_MAX_MSIX_MESSAGES_PER_CONTROLLER ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ISCI_INTERRUPT_INFO*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isci_interrupt_msix_handler ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  scic_controller_get_handler_methods (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isci_interrupt_setup_msix(struct isci_softc *isci)
{
	uint32_t controller_index;

	scic_controller_get_handler_methods(SCIC_MSIX_INTERRUPT_TYPE,
	    SCI_MAX_MSIX_MESSAGES_PER_CONTROLLER, &isci->handlers[0]);

	for (controller_index = 0; controller_index < isci->controller_count;
	    controller_index++) {
		uint32_t msix_index;
		uint8_t base_index = controller_index *
		    SCI_MAX_MSIX_MESSAGES_PER_CONTROLLER;

		for (msix_index = 0; msix_index < SCI_MAX_MSIX_MESSAGES_PER_CONTROLLER;
		    msix_index++) {
			struct ISCI_INTERRUPT_INFO *info =
			    &isci->interrupt_info[base_index+msix_index];

			info->handlers = &isci->handlers[msix_index];
			info->interrupt_target_handle =
			    &isci->controllers[controller_index];

			info->rid = base_index+msix_index+1;

			info->res = bus_alloc_resource_any(isci->device,
			    SYS_RES_IRQ, &info->rid, RF_ACTIVE);
			if (info->res == NULL) {
				isci_log_message(0, "ISCI",
				    "bus_alloc_resource failed\n");
				return (-1);
			}

			info->tag = NULL;
			if (bus_setup_intr(isci->device, info->res,
			    INTR_TYPE_CAM | INTR_MPSAFE, NULL,
			    isci_interrupt_msix_handler, info, &info->tag)) {
				isci_log_message(0, "ISCI",
				    "bus_setup_intr failed\n");
				return (-1);
			}
		}
	}

	return (0);
}