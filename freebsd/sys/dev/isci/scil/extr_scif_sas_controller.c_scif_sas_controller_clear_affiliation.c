#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_5__ {size_t current_domain_to_clear_affiliation; int /*<<< orphan*/ * domains; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCI_MAX_DOMAINS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCI_WARNING_SEQUENCE_INCOMPLETE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  scif_sas_controller_continue_to_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  scif_sas_domain_cancel_smp_activities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_start_clear_affiliation (int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_controller_clear_affiliation(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   U8 index;
   SCI_STATUS status;
   SCIF_SAS_DOMAIN_T * fw_domain;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER,
      "scif_sas_controller_clear_affiliation(0x%x) enter\n",
      fw_controller
   ));

   index = fw_controller->current_domain_to_clear_affiliation;

   if (index < SCI_MAX_DOMAINS)
   {
      fw_domain = &fw_controller->domains[index];

      //Need to stop all the on-going smp activities before clearing affiliation.
      scif_sas_domain_cancel_smp_activities(fw_domain);

      scif_sas_domain_start_clear_affiliation(fw_domain);

      status = SCI_WARNING_SEQUENCE_INCOMPLETE;
   }
   else
   {  //the controller has done clear affiliation work to all its domains.
      scif_sas_controller_continue_to_stop(fw_controller);
      status = SCI_SUCCESS;
   }

   return status;
}