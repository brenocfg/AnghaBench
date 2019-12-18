#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_5__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_request_default_abort_handler(
   SCI_BASE_REQUEST_T *request
)
{
   SCIC_LOG_WARNING((
      sci_base_object_get_logger((SCIC_SDS_REQUEST_T *)request),
      (
          SCIC_LOG_OBJECT_SSP_IO_REQUEST
        | SCIC_LOG_OBJECT_STP_IO_REQUEST
        | SCIC_LOG_OBJECT_SMP_IO_REQUEST
      ),
      "SCIC IO Request requested to abort while in wrong state %d\n",
      sci_base_state_machine_get_state(
         &((SCIC_SDS_REQUEST_T *)request)->parent.state_machine)
   ));

   return SCI_FAILURE_INVALID_STATE;
}