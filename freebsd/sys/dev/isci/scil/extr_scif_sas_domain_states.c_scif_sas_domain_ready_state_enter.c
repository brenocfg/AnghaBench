#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ previous_state_id; } ;
struct TYPE_11__ {TYPE_7__ state_machine; } ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_12__ {scalar_t__ broadcast_change_count; int /*<<< orphan*/  core_object; TYPE_2__ parent; int /*<<< orphan*/  controller; TYPE_1__ operation; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_3__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_READY ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_STARTING ; 
 scalar_t__ SCI_FAILURE_TIMEOUT ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  scic_port_enable_broadcast_change_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_domain_change_notification (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  scif_cb_domain_ready (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_domain_state_handler_table ; 
 int /*<<< orphan*/  scif_sas_domain_transition_from_discovering_state (TYPE_3__*) ; 

__attribute__((used)) static
void scif_sas_domain_ready_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T *)object;

   SET_STATE_HANDLER(
      fw_domain,
      scif_sas_domain_state_handler_table,
      SCI_BASE_DOMAIN_STATE_READY
   );

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_ready_state_enter(0x%x) enter\n",
      fw_domain
   ));

   if (fw_domain->parent.state_machine.previous_state_id
       == SCI_BASE_DOMAIN_STATE_STARTING)
   {
      scif_cb_domain_ready(fw_domain->controller, fw_domain);

      // Only indicate the domain change notification if the previous
      // state was the STARTING state.  We issue the notification here
      // as opposed to exit of the STARTING state so that the appropriate
      // state handlers are in place should the user call
      // scif_domain_discover() from scif_cb_domain_change_notification()
      scif_cb_domain_change_notification(fw_domain->controller, fw_domain);
   }
   else if (fw_domain->parent.state_machine.previous_state_id
            == SCI_BASE_DOMAIN_STATE_DISCOVERING)
   {
      //if domain discovery timed out, we will NOT go back to discover even
      //the broadcast change count is not zero. Instead we finish the discovery
      //back to user. User can check the operation status and decide to
      //retry discover all over again.
      if (fw_domain->operation.status == SCI_FAILURE_TIMEOUT)
         fw_domain->broadcast_change_count = 0;

      // Check the broadcast change count to determine if discovery
      // is indeed complete.
      if (fw_domain->broadcast_change_count == 0)
      {
         scif_sas_domain_transition_from_discovering_state(fw_domain);
         scif_cb_domain_ready(fw_domain->controller, fw_domain);
      }
      else
      {
         // The broadcast change count indicates something my have
         // changed in the domain, while a discovery was ongoing.
         // Thus, we should start discovery over again.
         sci_base_state_machine_change_state(
            &fw_domain->parent.state_machine, SCI_BASE_DOMAIN_STATE_DISCOVERING
         );
      }

      // Enable the BCN because underneath hardware may disabled any further
      // BCN.
      scic_port_enable_broadcast_change_notification(fw_domain->core_object);
   }
}