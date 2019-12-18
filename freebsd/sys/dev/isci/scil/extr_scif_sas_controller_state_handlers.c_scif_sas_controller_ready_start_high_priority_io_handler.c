#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_6__ {int /*<<< orphan*/  internal_io_timer; } ;
struct TYPE_4__ {scalar_t__ is_internal; } ;
struct TYPE_5__ {TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_2__ SCIF_SAS_IO_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_INTERNAL_IO_REQUEST_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_INTERNAL_REQUEST_TIMEOUT ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scif_sas_controller_common_start_high_priority_io_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_ready_start_high_priority_io_handler(
   SCI_BASE_CONTROLLER_T    * controller,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request,
   U16                        io_tag
)
{
   SCI_STATUS status;
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T *)io_request;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_controller_ready_start_high_priority_io_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, io_request, io_tag
   ));

   status = scif_sas_controller_common_start_high_priority_io_handler(
               controller, remote_device, io_request, io_tag);

   if (status == SCI_SUCCESS)
   {
      //External io could also be put in high priority queue. i.e. the
      //smp request for EA Target Reset.
      if (fw_io->parent.is_internal)
      {
         SCIF_SAS_INTERNAL_IO_REQUEST_T * fw_internal_io =
            (SCIF_SAS_INTERNAL_IO_REQUEST_T *)fw_io;

         //start the timer for internal io
         scif_cb_timer_start(
            (SCI_CONTROLLER_HANDLE_T)controller,
             fw_internal_io->internal_io_timer,
             SCIF_SAS_INTERNAL_REQUEST_TIMEOUT
         );
      }
   }
   else
   {
      //If failed to start, most likely the device or domain is not in
      //correct state, and the IO has been cleaned up in controller's start
      //high priority IO handler. We should just continue to start the next
      //IO in the HP queue.

      SCIF_LOG_TRACE((
         sci_base_object_get_logger(controller),
         SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_IO_REQUEST,
         "scif_controller_start_high_priority_io(0x%x, 0x%x), starting io failed\n",
         controller, fw_io
      ));
   }

   return status;
}