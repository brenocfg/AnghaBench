#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* count; } ;
struct TYPE_10__ {TYPE_3__ buffers; } ;
struct TYPE_7__ {scalar_t__ current_state_id; } ;
struct TYPE_8__ {TYPE_1__ state_machine; } ;
struct TYPE_11__ {void* completion_queue_entries; void* completion_event_entries; TYPE_4__ uf_control; void* task_context_entries; void* remote_node_entries; TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int SCI_CONTROLLER_MODE ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_5__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 void* MIN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZING ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  SCI_MAX_REMOTE_DEVICES ; 
 int /*<<< orphan*/  SCI_MIN_IO_REQUESTS ; 
 int /*<<< orphan*/  SCI_MIN_REMOTE_DEVICES ; 
#define  SCI_MODE_SIZE 129 
#define  SCI_MODE_SPEED 128 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_COMPLETION_QUEUE_COUNT ; 
 int /*<<< orphan*/  SCU_EVENT_COUNT ; 
 int /*<<< orphan*/  SCU_IO_REQUEST_COUNT ; 
 int /*<<< orphan*/  SCU_MIN_COMPLETION_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  SCU_MIN_EVENTS ; 
 int /*<<< orphan*/  SCU_MIN_UNSOLICITED_FRAMES ; 
 int /*<<< orphan*/  SCU_UNSOLICITED_FRAME_COUNT ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_controller_build_memory_descriptor_table (TYPE_5__*) ; 

SCI_STATUS scic_controller_set_mode(
   SCI_CONTROLLER_HANDLE_T   controller,
   SCI_CONTROLLER_MODE       operating_mode
)
{
   SCIC_SDS_CONTROLLER_T *this_controller = (SCIC_SDS_CONTROLLER_T*)controller;
   SCI_STATUS             status          = SCI_SUCCESS;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_set_mode(0x%x, 0x%x) enter\n",
      controller, operating_mode
   ));

   if (
         (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZING)
      || (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZED)
      )
   {
      switch (operating_mode)
      {
      case SCI_MODE_SPEED:
         this_controller->remote_node_entries =
            MIN(this_controller->remote_node_entries, SCI_MAX_REMOTE_DEVICES);
         this_controller->task_context_entries =
            MIN(this_controller->task_context_entries, SCU_IO_REQUEST_COUNT);
         this_controller->uf_control.buffers.count =
            MIN(this_controller->uf_control.buffers.count, SCU_UNSOLICITED_FRAME_COUNT);
         this_controller->completion_event_entries =
            MIN(this_controller->completion_event_entries, SCU_EVENT_COUNT);
         this_controller->completion_queue_entries =
            MIN(this_controller->completion_queue_entries, SCU_COMPLETION_QUEUE_COUNT);

         scic_sds_controller_build_memory_descriptor_table(this_controller);
      break;

      case SCI_MODE_SIZE:
         this_controller->remote_node_entries =
            MIN(this_controller->remote_node_entries, SCI_MIN_REMOTE_DEVICES);
         this_controller->task_context_entries =
            MIN(this_controller->task_context_entries, SCI_MIN_IO_REQUESTS);
         this_controller->uf_control.buffers.count =
            MIN(this_controller->uf_control.buffers.count, SCU_MIN_UNSOLICITED_FRAMES);
         this_controller->completion_event_entries =
            MIN(this_controller->completion_event_entries, SCU_MIN_EVENTS);
         this_controller->completion_queue_entries =
            MIN(this_controller->completion_queue_entries, SCU_MIN_COMPLETION_QUEUE_ENTRIES);

         scic_sds_controller_build_memory_descriptor_table(this_controller);
      break;

      default:
         status = SCI_FAILURE_INVALID_PARAMETER_VALUE;
      break;
      }
   }
   else
      status = SCI_FAILURE_INVALID_STATE;

   return status;
}