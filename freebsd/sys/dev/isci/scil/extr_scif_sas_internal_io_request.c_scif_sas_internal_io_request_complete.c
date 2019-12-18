#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  internal_io_timer; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIF_SAS_INTERNAL_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cb_timer_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_internal_io_request_destruct (int /*<<< orphan*/ *,TYPE_1__*) ; 

void scif_sas_internal_io_request_complete(
   SCIF_SAS_CONTROLLER_T          * fw_controller,
   SCIF_SAS_INTERNAL_IO_REQUEST_T * fw_internal_io,
   SCI_STATUS                       completion_status
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_internal_io_request_complete(0x%x, 0x%x, 0x%x) enter\n",
       fw_controller, fw_internal_io, completion_status
   ));

   scif_cb_timer_stop(fw_controller, fw_internal_io->internal_io_timer);
   scif_sas_internal_io_request_destruct(fw_controller, fw_internal_io);
}