#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  parent; } ;
struct TYPE_11__ {TYPE_2__ parent; int /*<<< orphan*/  command_buffer; int /*<<< orphan*/  started_substate_machine; int /*<<< orphan*/  has_started_substate_machine; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {scalar_t__ request_length; int function; } ;
struct TYPE_10__ {TYPE_1__ header; } ;
typedef  TYPE_3__ SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_SMP_REQUEST_STARTED_SUBSTATE_AWAIT_RESPONSE ; 
 int /*<<< orphan*/  SCIC_SMP_PROTOCOL ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
#define  SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION 134 
#define  SMP_FUNCTION_DISCOVER 133 
#define  SMP_FUNCTION_PHY_CONTROL 132 
#define  SMP_FUNCTION_PHY_TEST 131 
#define  SMP_FUNCTION_REPORT_PHY_ERROR_LOG 130 
#define  SMP_FUNCTION_REPORT_PHY_SATA 129 
#define  SMP_FUNCTION_REPORT_ROUTE_INFORMATION 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_smp_request_started_substate_table ; 
 int /*<<< orphan*/  scu_smp_request_construct_task_context (TYPE_4__*,TYPE_3__*) ; 

SCI_STATUS scic_io_request_construct_smp(
   SCI_IO_REQUEST_HANDLE_T  scic_smp_request
)
{
   SMP_REQUEST_T smp_request;

   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *) scic_smp_request;
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_SMP_IO_REQUEST,
      "scic_io_request_construct_smp(0x%x) enter\n",
      this_request
   ));

   this_request->protocol                     = SCIC_SMP_PROTOCOL;
   this_request->has_started_substate_machine = TRUE;

   // Construct the started sub-state machine.
   sci_base_state_machine_construct(
      &this_request->started_substate_machine,
      &this_request->parent.parent,
      scic_sds_smp_request_started_substate_table,
      SCIC_SDS_SMP_REQUEST_STARTED_SUBSTATE_AWAIT_RESPONSE
   );

   // Construct the SMP SCU Task Context
   memcpy((char *)&smp_request,
        this_request->command_buffer,
        sizeof(SMP_REQUEST_T));

   // Look at the SMP requests' header fields; for certain SAS 1.x SMP
   // functions under SAS 2.0, a zero request length really indicates
   // a non-zero default length.
   if( smp_request.header.request_length == 0 )
   {
       switch( smp_request.header.function )
       {
       case SMP_FUNCTION_DISCOVER:
       case SMP_FUNCTION_REPORT_PHY_ERROR_LOG:
       case SMP_FUNCTION_REPORT_PHY_SATA:
       case SMP_FUNCTION_REPORT_ROUTE_INFORMATION:
           smp_request.header.request_length = 2;
           break;
       case SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION:
       case SMP_FUNCTION_PHY_CONTROL:
       case SMP_FUNCTION_PHY_TEST:
           smp_request.header.request_length = 9;
           break;
       // Default - zero is a valid default for 2.0.
       }
   }

   scu_smp_request_construct_task_context(
      this_request,
      &smp_request
   );

   sci_base_state_machine_change_state(
      &this_request->parent.state_machine,
      SCI_BASE_REQUEST_STATE_CONSTRUCTED
   );

   return SCI_SUCCESS;
}