#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCI_BASE_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_discovering_port_not_ready_handler(
   SCI_BASE_DOMAIN_T * domain,
   U32                 reason_code
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_discovering_port_not_ready_handler(0x%x, 0x%x) enter\n",
      domain,
      reason_code
   ));

   // Change to the STOPPING state to cause existing request
   // completions to be terminated and devices removed.
   sci_base_state_machine_change_state(
      &domain->state_machine, SCI_BASE_DOMAIN_STATE_STOPPING
   );

   return SCI_SUCCESS;
}