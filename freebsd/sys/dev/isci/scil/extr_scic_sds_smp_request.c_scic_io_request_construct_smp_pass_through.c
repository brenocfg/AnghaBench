#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  int U32 ;
struct TYPE_13__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  parent; } ;
struct TYPE_16__ {TYPE_3__ parent; int /*<<< orphan*/  started_substate_machine; int /*<<< orphan*/  has_started_substate_machine; int /*<<< orphan*/  protocol; } ;
struct TYPE_15__ {int (* scic_cb_smp_passthru_get_request ) (void*,scalar_t__**) ;int /*<<< orphan*/  (* scic_cb_smp_passthru_get_allocated_response_length ) (void*) ;int /*<<< orphan*/  (* scic_cb_smp_passthru_get_function ) (void*) ;int /*<<< orphan*/  (* scic_cb_smp_passthru_get_frame_type ) (void*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  allocated_response_length; int /*<<< orphan*/  function; int /*<<< orphan*/  smp_frame_type; scalar_t__ request_length; } ;
struct TYPE_11__ {int /*<<< orphan*/  vendor_specific_request; } ;
struct TYPE_14__ {TYPE_2__ header; TYPE_1__ request; } ;
typedef  TYPE_4__ SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_5__ SCIC_SMP_PASSTHRU_REQUEST_CALLBACKS_T ;
typedef  TYPE_6__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_SMP_REQUEST_STARTED_SUBSTATE_AWAIT_RESPONSE ; 
 int /*<<< orphan*/  SCIC_SMP_PROTOCOL ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_smp_request_started_substate_table ; 
 int /*<<< orphan*/  scu_smp_request_construct_task_context (TYPE_6__*,TYPE_4__*) ; 
 int stub1 (void*,scalar_t__**) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 

SCI_STATUS scic_io_request_construct_smp_pass_through(
   SCI_IO_REQUEST_HANDLE_T  scic_smp_request,
   SCIC_SMP_PASSTHRU_REQUEST_CALLBACKS_T *passthru_cb
)
{
   SMP_REQUEST_T smp_request;
   U8 * request_buffer;
   U32 request_buffer_length_in_bytes;

   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *) scic_smp_request;
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_SMP_IO_REQUEST,
      "scic_io_request_construct_smp_pass_through(0x%x) enter\n",
      this_request
   ));

   this_request->protocol                     = SCIC_SMP_PROTOCOL;
   this_request->has_started_substate_machine = TRUE;

   // Call the callback function to retrieve the SMP passthrough request
   request_buffer_length_in_bytes = passthru_cb->scic_cb_smp_passthru_get_request (
                                       (void *)this_request,
                                       &request_buffer
                                    );

   //copy the request to smp request
   memcpy((char *)&smp_request.request.vendor_specific_request,
        request_buffer,
        request_buffer_length_in_bytes);

   //the header length in smp_request is in dwords - the sas spec has similar way,
   //but the csmi header contains the number of bytes, so we need to convert the
   //number of bytes to number of dwords
   smp_request.header.request_length = (U8) (request_buffer_length_in_bytes / sizeof (U32));

   //Grab the other needed fields from the smp request using callbacks
   smp_request.header.smp_frame_type = passthru_cb->scic_cb_smp_passthru_get_frame_type ((void *)this_request);
   smp_request.header.function = passthru_cb->scic_cb_smp_passthru_get_function ((void *)this_request);
   smp_request.header.allocated_response_length = passthru_cb->scic_cb_smp_passthru_get_allocated_response_length((void *)this_request);

   // Construct the started sub-state machine.
   sci_base_state_machine_construct(
      &this_request->started_substate_machine,
      &this_request->parent.parent,
      scic_sds_smp_request_started_substate_table,
      SCIC_SDS_SMP_REQUEST_STARTED_SUBSTATE_AWAIT_RESPONSE
   );

   // Construct the SMP SCU Task Context
   scu_smp_request_construct_task_context (this_request, &smp_request);

   sci_base_state_machine_change_state(
      &this_request->parent.state_machine,
      SCI_BASE_REQUEST_STATE_CONSTRUCTED
   );

   return SCI_SUCCESS;
}