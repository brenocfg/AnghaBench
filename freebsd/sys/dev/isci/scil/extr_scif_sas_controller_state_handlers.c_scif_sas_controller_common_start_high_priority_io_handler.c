#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_22__ {int /*<<< orphan*/  core_object; scalar_t__ is_internal; TYPE_2__* state_handlers; } ;
struct TYPE_28__ {scalar_t__ retry_count; TYPE_3__ parent; } ;
struct TYPE_24__ {int /*<<< orphan*/ * smp_activity_timer; } ;
struct TYPE_25__ {TYPE_5__ smp_device; } ;
struct TYPE_27__ {TYPE_6__ protocol_device; TYPE_4__* domain; int /*<<< orphan*/  core_object; } ;
struct TYPE_26__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_23__ {int /*<<< orphan*/  controller; int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* complete_handler ) (TYPE_7__*) ;} ;
struct TYPE_20__ {scalar_t__ (* start_high_priority_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ;int /*<<< orphan*/  (* complete_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  core_object; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_7__ SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_8__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_9__ SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_INTERNAL_IO_REQUEST_T ;
typedef  TYPE_10__ SCIF_SAS_CONTROLLER_T ;
typedef  scalar_t__ SCIC_TRANSPORT_PROTOCOL ;

/* Variables and functions */
 scalar_t__ SCIC_SMP_PROTOCOL ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIF_SAS_IO_RETRY_LIMIT ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_STARTED ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SMP_REQUEST_RETRY_WAIT_DURATION ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_10__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_controller_start_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_io_request_get_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_timer_destroy (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_internal_io_request_destruct (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_retry_internal_io (TYPE_8__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__*) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_common_start_high_priority_io_handler(
   SCI_BASE_CONTROLLER_T    * controller,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request,
   U16                        io_tag
)
{
   SCI_STATUS                status;
   SCIF_SAS_IO_REQUEST_T    *fw_io         = (SCIF_SAS_IO_REQUEST_T*)io_request;
   SCIF_SAS_CONTROLLER_T    *fw_controller = (SCIF_SAS_CONTROLLER_T*)controller;
   SCIF_SAS_REMOTE_DEVICE_T *fw_device     = (SCIF_SAS_REMOTE_DEVICE_T*)
                                             remote_device;

   status = fw_device->domain->state_handlers->start_high_priority_io_handler(
               &fw_device->domain->parent, remote_device, io_request
            );

   // Check to see that the other objects in the framework allowed
   // this IO to be started.
   if (status == SCI_SUCCESS)
   {
      // Ask the core to start processing for this IO request.
      status = (SCI_STATUS)scic_controller_start_io(
                  fw_controller->core_object,
                  fw_device->core_object,
                  fw_io->parent.core_object,
                  io_tag
               );

      if (status == SCI_SUCCESS)
      {
         // We were able to start the core request. As a result,
         // commit to starting the request for the framework by changing
         // the state of the IO request.
         sci_base_state_machine_change_state(
            &io_request->state_machine, SCI_BASE_REQUEST_STATE_STARTED
         );
      }
      else
      {
         // We were unable to start the core IO request. As a result,
         // back out the start operation for the framework.  It's easier to
         // back out the framework start operation then to backout the core
         // start IO operation.
         fw_device->domain->state_handlers->complete_io_handler(
            &fw_device->domain->parent, remote_device, io_request
         );

         // Invoke the IO completion handler.  For most IOs, this does nothing
         // since we are still in the constructed state.  For NCQ, this will
         // the return of the NCQ tag back to the remote device free pool.
         fw_io->parent.state_handlers->complete_handler(io_request);

         SCIF_LOG_WARNING((
            sci_base_object_get_logger(fw_controller),
            SCIF_LOG_OBJECT_CONTROLLER,
            "Controller:0x%x IORequest:0x%x Status:0x%x core IO start failed\n",
            fw_controller, fw_io, status
         ));
      }
   }
   else
   {
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER,
         "Controller:0x%x IORequest:0x%x Status:0x%x IO start failed\n",
         fw_controller, fw_io, status
      ));

      // Invoke the IO completion handler.  For most IOs, this does nothing
      // since we are still in the constructed state.  For NCQ, this will
      // the return of the NCQ tag back to the remote device free pool.
      fw_io->parent.state_handlers->complete_handler(io_request);

   }

   if (fw_io->parent.is_internal && status != SCI_SUCCESS )
   {
      SCIC_TRANSPORT_PROTOCOL protocol =
         scic_io_request_get_protocol(fw_io->parent.core_object);

      U8 retry_count = fw_io->retry_count;

      scif_sas_internal_io_request_destruct(
         fw_device->domain->controller,
         (SCIF_SAS_INTERNAL_IO_REQUEST_T *)fw_io
      );

      if ( protocol == SCIC_SMP_PROTOCOL )
      {
         if (fw_device->protocol_device.smp_device.smp_activity_timer != NULL)
         {
            //destroy the smp_activity_timer
            scif_cb_timer_destroy (
               fw_controller,
               fw_device->protocol_device.smp_device.smp_activity_timer
            );

            fw_device->protocol_device.smp_device.smp_activity_timer = NULL;
         }

         //we should retry for finite times
         if ( retry_count < SCIF_SAS_IO_RETRY_LIMIT)
         {
         //An internal smp request failed being started, most likely due to remote device
         //is not in ready state, for example, UPDATING_PORT_WIDTH state. In this case,
         //we should retry the IO.
         scif_sas_smp_remote_device_retry_internal_io(
            (SCIF_SAS_REMOTE_DEVICE_T *)remote_device,
            retry_count,
            SMP_REQUEST_RETRY_WAIT_DURATION
         );
      }
   }
   }

   return status;
}