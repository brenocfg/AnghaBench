#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_9__ {TYPE_2__ operation; TYPE_1__ parent; } ;
typedef  TYPE_3__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 int /*<<< orphan*/  SCI_FAILURE_TIMEOUT ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 scalar_t__ sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_cancel_smp_activities (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_domain_continue_discover (TYPE_3__*) ; 

__attribute__((used)) static
void scif_sas_domain_operation_timeout_handler(
   void * cookie
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T*) cookie;
   U32                 state;

   state = sci_base_state_machine_get_state(&fw_domain->parent.state_machine);

   // Based upon the state of the domain, we know whether we were in the
   // process of performing discovery or a reset.
   if (state == SCI_BASE_DOMAIN_STATE_DISCOVERING)
   {
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(fw_domain),
         SCIF_LOG_OBJECT_DOMAIN,
         "Domain:0x%x State:0x%x DISCOVER timeout!\n",
         fw_domain, state
      ));

      fw_domain->operation.status = SCI_FAILURE_TIMEOUT;

      //search all the smp devices in the domain and cancel their activities
      //if there is any outstanding activity remained. The smp devices will terminate
      //all the started internal IOs.
      scif_sas_domain_cancel_smp_activities(fw_domain);

      scif_sas_domain_continue_discover(fw_domain);
   }
   else
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_domain),
         SCIF_LOG_OBJECT_DOMAIN,
         "Domain:0x%x State:0x%x operation timeout in invalid state\n",
         fw_domain, state
      ));
   }
}