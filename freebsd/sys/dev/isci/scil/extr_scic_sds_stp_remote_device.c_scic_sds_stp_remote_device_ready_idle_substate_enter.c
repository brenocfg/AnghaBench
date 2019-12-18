#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rnc; int /*<<< orphan*/ * working_request; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_IDLE ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_remote_node_context_is_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_resume (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*),TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_stp_remote_device_ready_idle_substate_resume_complete_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_stp_remote_device_ready_substate_handler_table ; 

__attribute__((used)) static
void scic_sds_stp_remote_device_ready_idle_substate_enter(
   SCI_BASE_OBJECT_T * device
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device;

   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;

   SET_STATE_HANDLER(
      this_device,
      scic_sds_stp_remote_device_ready_substate_handler_table,
      SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_IDLE
   );

   this_device->working_request = NULL;

   if (scic_sds_remote_node_context_is_ready(this_device->rnc))
   {
      // Since the RNC is ready, it's alright to finish completion
      // processing (e.g. signal the remote device is ready).
      scic_sds_stp_remote_device_ready_idle_substate_resume_complete_handler(
         this_device
      );
   }
   else
   {
      scic_sds_remote_node_context_resume(
         this_device->rnc,
         scic_sds_stp_remote_device_ready_idle_substate_resume_complete_handler,
         this_device
      );
   }
}