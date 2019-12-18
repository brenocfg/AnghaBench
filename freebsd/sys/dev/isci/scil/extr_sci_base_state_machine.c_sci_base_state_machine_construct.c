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
typedef  void* U32 ;
struct TYPE_3__ {int /*<<< orphan*/ * state_table; void* current_state_id; void* previous_state_id; void* initial_state_id; int /*<<< orphan*/ * state_machine_owner; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_STATE_T ;
typedef  TYPE_1__ SCI_BASE_STATE_MACHINE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;

/* Variables and functions */
 int /*<<< orphan*/  sci_base_subject_construct (int /*<<< orphan*/ *) ; 

void sci_base_state_machine_construct(
   SCI_BASE_STATE_MACHINE_T * this_state_machine,
   SCI_BASE_OBJECT_T        * my_state_machine_owner,
   SCI_BASE_STATE_T         * state_table,
   U32                        initial_state
)
{
#if defined(SCI_LOGGING)
   sci_base_subject_construct(&this_state_machine->parent);
#endif // defined(SCI_LOGGING)

   this_state_machine->state_machine_owner = my_state_machine_owner;
   this_state_machine->initial_state_id  = initial_state;
   this_state_machine->previous_state_id = initial_state;
   this_state_machine->current_state_id  = initial_state;
   this_state_machine->state_table       = state_table;
}