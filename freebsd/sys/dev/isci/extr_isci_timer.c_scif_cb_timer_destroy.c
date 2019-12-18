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
struct ISCI_TIMER {int dummy; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  timer_pool; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  isci_log_message (int,char*,char*,void*) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,struct ISCI_TIMER*) ; 
 int /*<<< orphan*/  scif_cb_timer_stop (int /*<<< orphan*/ ,void*) ; 

void
scif_cb_timer_destroy(SCI_CONTROLLER_HANDLE_T scif_controller,
    void *timer_handle)
{
	struct ISCI_CONTROLLER *isci_controller = (struct ISCI_CONTROLLER *)
	    sci_object_get_association(scif_controller);

	scif_cb_timer_stop(scif_controller, timer_handle);
	sci_pool_put(isci_controller->timer_pool, (struct ISCI_TIMER *)timer_handle);

	isci_log_message(3, "TIMER", "destroy %p\n", timer_handle);
}