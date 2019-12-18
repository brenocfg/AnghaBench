#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* state_handlers; } ;
struct TYPE_7__ {int /*<<< orphan*/  ready_substate_machine; int /*<<< orphan*/ * working_request; int /*<<< orphan*/  rnc; TYPE_3__* owning_port; } ;
struct TYPE_6__ {scalar_t__ (* start_io_handler ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_2__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_CMD ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_start_request (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ scic_sds_remote_node_context_start_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_request_start (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_smp_remote_device_ready_idle_substate_start_io_handler(
   SCI_BASE_REMOTE_DEVICE_T * device,
   SCI_BASE_REQUEST_T       * request
)
{
   SCI_STATUS status;
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;
   SCIC_SDS_REQUEST_T       * io_request  = (SCIC_SDS_REQUEST_T       *)request;

   // Will the port allow the io request to start?
   status = this_device->owning_port->state_handlers->start_io_handler(
      this_device->owning_port,
      this_device,
      io_request
   );

   if (status == SCI_SUCCESS)
   {
      status =
         scic_sds_remote_node_context_start_io(this_device->rnc, io_request);

      if (status == SCI_SUCCESS)
      {
         status = scic_sds_request_start(io_request);
      }

      if (status == SCI_SUCCESS)
      {
         this_device->working_request = io_request;

         sci_base_state_machine_change_state(
               &this_device->ready_substate_machine,
               SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_CMD
         );
      }

      scic_sds_remote_device_start_request(this_device, io_request, status);
   }

   return status;
}