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
struct TYPE_5__ {TYPE_1__ parent; int /*<<< orphan*/  controller; } ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_save_interrupt_coalescence (int /*<<< orphan*/ ) ; 

void scif_sas_domain_transition_to_discovering_state(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   scif_sas_controller_save_interrupt_coalescence(fw_domain->controller);

   sci_base_state_machine_change_state(
      &fw_domain->parent.state_machine, SCI_BASE_DOMAIN_STATE_DISCOVERING
   );
}