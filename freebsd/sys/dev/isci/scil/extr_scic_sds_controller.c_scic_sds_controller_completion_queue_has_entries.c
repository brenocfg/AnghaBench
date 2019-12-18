#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_3__ {size_t completion_queue_get; int /*<<< orphan*/ * completion_queue; } ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ COMPLETION_QUEUE_CYCLE_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NORMALIZE_GET_POINTER_CYCLE_BIT (size_t) ; 
 size_t SMU_COMPLETION_QUEUE_GET_POINTER_MASK ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL scic_sds_controller_completion_queue_has_entries(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32 get_value = this_controller->completion_queue_get;
   U32 get_index = get_value & SMU_COMPLETION_QUEUE_GET_POINTER_MASK;
   if (
           NORMALIZE_GET_POINTER_CYCLE_BIT(get_value)
        == COMPLETION_QUEUE_CYCLE_BIT(this_controller->completion_queue[get_index])
      )
   {
      return TRUE;
   }

   return FALSE;
}