#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_10__ {scalar_t__ current_state_id; } ;
struct TYPE_9__ {TYPE_2__* domains; } ;
struct TYPE_7__ {TYPE_5__ state_machine; } ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;
typedef  TYPE_3__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_READY ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_STOPPING ; 
 size_t SCI_MAX_DOMAINS ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_stop_domains(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   U8 index;
   SCI_STATUS status = SCI_SUCCESS;
   SCIF_SAS_DOMAIN_T * fw_domain;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER,
      "scif_sas_controller_stop_domains(0x%x) enter\n",
      fw_controller
   ));

   for (index = 0; index < SCI_MAX_DOMAINS && status == SCI_SUCCESS; index++)
   {
      fw_domain = &fw_controller->domains[index];

      //Change this domain to STOPPING state. All the remote devices will be
      //stopped subsquentially.
      if (fw_domain->parent.state_machine.current_state_id ==
             SCI_BASE_DOMAIN_STATE_READY
          || fw_domain->parent.state_machine.current_state_id ==
             SCI_BASE_DOMAIN_STATE_DISCOVERING)
      {
         sci_base_state_machine_change_state(
            &fw_domain->parent.state_machine, SCI_BASE_DOMAIN_STATE_STOPPING
         );
      }
   }

   return status;
}