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
struct TYPE_4__ {int /*<<< orphan*/ * internal_io_timer; } ;
typedef  TYPE_1__ SCIF_SAS_INTERNAL_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cb_timer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_controller_free_internal_request (int /*<<< orphan*/ *,TYPE_1__*) ; 

void scif_sas_internal_io_request_destruct(
   SCIF_SAS_CONTROLLER_T          * fw_controller,
   SCIF_SAS_INTERNAL_IO_REQUEST_T * fw_internal_io
)
{
   if (fw_internal_io->internal_io_timer != NULL)
   {
      scif_cb_timer_destroy(fw_controller, fw_internal_io->internal_io_timer);
      fw_internal_io->internal_io_timer = NULL;
   }
   scif_sas_controller_free_internal_request(fw_controller, fw_internal_io);
}