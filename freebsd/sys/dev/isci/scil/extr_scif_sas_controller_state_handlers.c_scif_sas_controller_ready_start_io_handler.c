#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_21__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_17__ {TYPE_3__* state_handlers; int /*<<< orphan*/  core_object; } ;
struct TYPE_20__ {TYPE_4__ parent; } ;
struct TYPE_19__ {TYPE_2__* domain; int /*<<< orphan*/  core_object; } ;
struct TYPE_18__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* complete_handler ) (TYPE_5__*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_14__ {scalar_t__ (* start_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ;int /*<<< orphan*/  (* complete_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_5__ SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_7__ SCIF_SAS_IO_REQUEST_T ;
typedef  TYPE_8__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_STARTED ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_8__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_controller_start_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_ready_start_io_handler(
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

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_controller_ready_start_io_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, io_request, io_tag
   ));

   status = fw_device->domain->state_handlers->start_io_handler(
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
   }

   return status;
}