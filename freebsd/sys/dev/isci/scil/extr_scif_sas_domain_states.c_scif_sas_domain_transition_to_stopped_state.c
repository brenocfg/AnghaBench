#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {scalar_t__ element_count; } ;
struct TYPE_8__ {scalar_t__ device_start_count; TYPE_2__ parent; TYPE_1__ request_list; } ;
typedef  TYPE_3__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_STOPPED ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scif_sas_domain_transition_to_stopped_state(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_transition_to_stopped_state(0x%x) enter\n",
      fw_domain
   ));

   // If IOs are quiesced, and all remote devices are stopped,
   // then transition directly to the STOPPED state.
   if (  (fw_domain->request_list.element_count == 0)
      && (fw_domain->device_start_count == 0) )
   {
      SCIF_LOG_INFO((
         sci_base_object_get_logger(fw_domain),
         SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
         "Domain:0x%x immediate transition to STOPPED\n",
         fw_domain
      ));

      sci_base_state_machine_change_state(
         &fw_domain->parent.state_machine, SCI_BASE_DOMAIN_STATE_STOPPED
      );
   }
}