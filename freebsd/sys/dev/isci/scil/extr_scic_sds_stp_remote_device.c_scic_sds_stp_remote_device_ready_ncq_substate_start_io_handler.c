#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* state_handlers; } ;
struct TYPE_16__ {int /*<<< orphan*/  rnc; TYPE_6__* owning_port; } ;
struct TYPE_15__ {scalar_t__ sat_protocol; TYPE_3__* state_handlers; } ;
struct TYPE_13__ {scalar_t__ (* start_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_2__ parent; } ;
struct TYPE_12__ {scalar_t__ (* start_io_handler ) (TYPE_6__*,TYPE_5__*,TYPE_4__*) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;
typedef  TYPE_5__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SAT_PROTOCOL_FPDMA ; 
 scalar_t__ SCI_FAILURE_INVALID_STATE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_remote_device_start_request (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 scalar_t__ scic_sds_remote_node_context_start_io (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_remote_device_ready_ncq_substate_start_io_handler(
   SCI_BASE_REMOTE_DEVICE_T * device,
   SCI_BASE_REQUEST_T       * request
)
{
   SCI_STATUS status;
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;
   SCIC_SDS_REQUEST_T       * io_request  = (SCIC_SDS_REQUEST_T       *)request;

   if (io_request->sat_protocol == SAT_PROTOCOL_FPDMA)
   {
      status = this_device->owning_port->state_handlers->start_io_handler(
         this_device->owning_port,
         this_device,
         io_request
      );

      if (status == SCI_SUCCESS)
      {
         status = scic_sds_remote_node_context_start_io(this_device->rnc, io_request);

         if (status == SCI_SUCCESS)
         {
            status = io_request->state_handlers->parent.start_handler(request);
         }

         scic_sds_remote_device_start_request(this_device, io_request, status);
      }
   }
   else
   {
      status = SCI_FAILURE_INVALID_STATE;
   }

   return status;
}