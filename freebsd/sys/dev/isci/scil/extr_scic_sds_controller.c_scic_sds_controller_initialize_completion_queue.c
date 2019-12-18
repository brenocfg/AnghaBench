#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_6__ {size_t completion_queue_get; size_t completion_queue_entries; int* completion_queue; scalar_t__ completion_event_entries; } ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  EVENT_ENABLE ; 
 int /*<<< orphan*/  EVENT_POINTER ; 
 int /*<<< orphan*/  POINTER ; 
 size_t SMU_CQC_EVENT_LIMIT_SET (scalar_t__) ; 
 size_t SMU_CQC_QUEUE_LIMIT_SET (size_t) ; 
 int /*<<< orphan*/  SMU_CQC_WRITE (TYPE_1__*,size_t) ; 
 size_t SMU_CQGR_GEN_BIT (int /*<<< orphan*/ ) ; 
 size_t SMU_CQGR_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_CQGR_WRITE (TYPE_1__*,size_t) ; 
 size_t SMU_CQPR_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_CQPR_WRITE (TYPE_1__*,size_t) ; 

void scic_sds_controller_initialize_completion_queue(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32 index;
   U32 completion_queue_control_value;
   U32 completion_queue_get_value;
   U32 completion_queue_put_value;

   this_controller->completion_queue_get = 0;

   completion_queue_control_value = (
        SMU_CQC_QUEUE_LIMIT_SET(this_controller->completion_queue_entries - 1)
      | SMU_CQC_EVENT_LIMIT_SET(this_controller->completion_event_entries - 1)
   );

   SMU_CQC_WRITE(this_controller, completion_queue_control_value);

   // Set the completion queue get pointer and enable the queue
   completion_queue_get_value = (
        (SMU_CQGR_GEN_VAL(POINTER, 0))
      | (SMU_CQGR_GEN_VAL(EVENT_POINTER, 0))
      | (SMU_CQGR_GEN_BIT(ENABLE))
      | (SMU_CQGR_GEN_BIT(EVENT_ENABLE))
   );

   SMU_CQGR_WRITE(this_controller, completion_queue_get_value);

   this_controller->completion_queue_get = completion_queue_get_value;

   // Set the completion queue put pointer
   completion_queue_put_value = (
        (SMU_CQPR_GEN_VAL(POINTER, 0))
      | (SMU_CQPR_GEN_VAL(EVENT_POINTER, 0))
   );

   SMU_CQPR_WRITE(this_controller, completion_queue_put_value);

   // Initialize the cycle bit of the completion queue entries
   for (index = 0; index < this_controller->completion_queue_entries; index++)
   {
      // If get.cycle_bit != completion_queue.cycle_bit
      // its not a valid completion queue entry
      // so at system start all entries are invalid
      this_controller->completion_queue[index] = 0x80000000;
   }
}