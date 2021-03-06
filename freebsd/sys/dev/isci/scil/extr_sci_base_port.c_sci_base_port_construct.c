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
struct TYPE_3__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_STATE_T ;
typedef  TYPE_1__ SCI_BASE_PORT_T ;
typedef  int /*<<< orphan*/  SCI_BASE_LOGGER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_STOPPED ; 
 int /*<<< orphan*/  sci_base_object_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_start (int /*<<< orphan*/ *) ; 

void sci_base_port_construct(
   SCI_BASE_PORT_T   *this_port,
   SCI_BASE_LOGGER_T *logger,
   SCI_BASE_STATE_T  *state_table
)
{
   sci_base_object_construct(&this_port->parent, logger);

   sci_base_state_machine_construct(
      &this_port->state_machine,
      &this_port->parent,
      state_table,
      SCI_BASE_PORT_STATE_STOPPED
   );

   sci_base_state_machine_start(
      &this_port->state_machine
   );
}