#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {TYPE_1__ parent; } ;
struct TYPE_7__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_io_request_default_destruct_handler(
   SCI_BASE_REQUEST_T * io_request
)
{
   SCIF_LOG_ERROR((
      sci_base_object_get_logger((SCIF_SAS_IO_REQUEST_T *) io_request),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "IoRequest:0x%x State:0x%x invalid state to destruct.\n",
      io_request,
      sci_base_state_machine_get_state(
         &((SCIF_SAS_IO_REQUEST_T *) io_request)->parent.parent.state_machine)
   ));

   return SCI_FAILURE_INVALID_STATE;
}