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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int /*<<< orphan*/  current_state_id; } ;
typedef  TYPE_1__ SCI_BASE_STATE_MACHINE_T ;

/* Variables and functions */

U32 sci_base_state_machine_get_state(
   SCI_BASE_STATE_MACHINE_T *this_state_machine
)
{
   return this_state_machine->current_state_id;
}