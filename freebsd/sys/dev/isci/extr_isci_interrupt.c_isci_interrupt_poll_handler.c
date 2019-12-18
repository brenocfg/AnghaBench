#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ISCI_CONTROLLER {int /*<<< orphan*/  scif_controller_handle; } ;
struct TYPE_3__ {scalar_t__ (* interrupt_handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* completion_handler ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_CONTROLLER_HANDLER_METHODS_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_NO_INTERRUPTS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  scic_controller_get_handler_methods (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  scif_controller_get_scic_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void
isci_interrupt_poll_handler(struct ISCI_CONTROLLER *controller)
{
	SCI_CONTROLLER_HANDLE_T scic_controller =
	    scif_controller_get_scic_handle(controller->scif_controller_handle);
	SCIC_CONTROLLER_HANDLER_METHODS_T handlers;

	scic_controller_get_handler_methods(SCIC_NO_INTERRUPTS, 0x0, &handlers);

	if(handlers.interrupt_handler(scic_controller) == TRUE) {
		/* Do not acquire controller lock in this path. xpt
		 *  poll routine will get called with this lock already
		 *  held, so we can't acquire it again here.  Other users
		 *  of this function must acquire the lock explicitly
		 *  before calling this handler.
		 */
		handlers.completion_handler(scic_controller);
	}
}