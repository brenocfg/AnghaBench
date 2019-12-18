#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ previous_state_id; } ;
struct TYPE_6__ {TYPE_1__ ready_substate_machine; } ;
typedef  TYPE_2__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_NCQ ; 
 int /*<<< orphan*/  scic_cb_remote_device_ready (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_controller (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_stp_remote_device_ready_idle_substate_resume_complete_handler(
   void * user_cookie
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device;
   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)user_cookie;

   // For NCQ operation we do not issue a
   // scic_cb_remote_device_not_ready().  As a result, avoid sending
   // the ready notification.
   if (this_device->ready_substate_machine.previous_state_id
       != SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_NCQ)
   {
      scic_cb_remote_device_ready(
         scic_sds_remote_device_get_controller(this_device), this_device
      );
   }
}