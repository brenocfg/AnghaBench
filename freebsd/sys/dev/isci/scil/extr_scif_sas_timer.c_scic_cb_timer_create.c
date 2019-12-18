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
typedef  int /*<<< orphan*/  SCI_TIMER_CALLBACK_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 void* scif_cb_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void * scic_cb_timer_create(
   SCI_CONTROLLER_HANDLE_T   controller,
   SCI_TIMER_CALLBACK_T      timer_callback,
   void                    * cookie
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T *)
                                         sci_object_get_association(controller);

   return scif_cb_timer_create(fw_controller, timer_callback, cookie);
}