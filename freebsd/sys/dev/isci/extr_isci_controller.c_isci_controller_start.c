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
struct ISCI_CONTROLLER {int /*<<< orphan*/  scif_controller_handle; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_controller_enable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_get_scic_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_get_suggested_start_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void isci_controller_start(void *controller_handle)
{
	struct ISCI_CONTROLLER *controller =
	    (struct ISCI_CONTROLLER *)controller_handle;
	SCI_CONTROLLER_HANDLE_T scif_controller_handle =
	    controller->scif_controller_handle;

	scif_controller_start(scif_controller_handle,
	    scif_controller_get_suggested_start_timeout(scif_controller_handle));

	scic_controller_enable_interrupts(
	    scif_controller_get_scic_handle(controller->scif_controller_handle));
}