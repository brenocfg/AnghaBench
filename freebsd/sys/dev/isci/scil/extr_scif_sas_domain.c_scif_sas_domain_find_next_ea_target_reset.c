#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  remote_device_list; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ea_target_reset_request_scheduled; } ;
typedef  int /*<<< orphan*/  SCI_ABSTRACT_ELEMENT_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sci_abstract_list_get_front (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sci_abstract_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_abstract_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 

SCIF_SAS_REMOTE_DEVICE_T * scif_sas_domain_find_next_ea_target_reset(
   SCIF_SAS_DOMAIN_T     * fw_domain
)
{
   SCI_ABSTRACT_ELEMENT_T   * current_element;
   SCIF_SAS_REMOTE_DEVICE_T * current_device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "scif_sas_domain_find_next_ea_target_reset(0x%x) enter\n",
      fw_domain
   ));

   //search through domain's device list to find the first sata device on spinup_hold
   current_element = sci_abstract_list_get_front(&fw_domain->remote_device_list);
   while (current_element != NULL )
   {
      current_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                       sci_abstract_list_get_object(current_element);

      current_element = sci_abstract_list_get_next(current_element);

      if ( current_device->ea_target_reset_request_scheduled != NULL )
      {
         return current_device;
      }
   }

   return NULL;
}