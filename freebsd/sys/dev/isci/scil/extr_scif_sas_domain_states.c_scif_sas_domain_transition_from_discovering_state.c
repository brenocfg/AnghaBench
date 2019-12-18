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
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  timer; } ;
struct TYPE_8__ {scalar_t__ previous_state_id; } ;
struct TYPE_9__ {TYPE_1__ state_machine; } ;
struct TYPE_11__ {TYPE_3__ operation; int /*<<< orphan*/  controller; TYPE_2__ parent; } ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_cb_domain_discovery_complete (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_restore_interrupt_coalescence (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scif_sas_domain_transition_from_discovering_state(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_transition_from_discovering_state(0x%x) enter\n",
      fw_domain
   ));

   if (fw_domain->parent.state_machine.previous_state_id
       == SCI_BASE_DOMAIN_STATE_DISCOVERING)
   {
      scif_sas_controller_restore_interrupt_coalescence(fw_domain->controller);

      scif_cb_timer_stop(fw_domain->controller, fw_domain->operation.timer);

      scif_cb_domain_discovery_complete(
         fw_domain->controller, fw_domain, fw_domain->operation.status
      );
   }
}