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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  remote_device_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_9__ {scalar_t__ low; scalar_t__ high; } ;
typedef  TYPE_1__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_2__* SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  scalar_t__ SCI_DOMAIN_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_ABSTRACT_ELEMENT_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 TYPE_2__* SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/ * sci_abstract_list_get_front (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sci_abstract_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_abstract_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_remote_device_get_sas_address (int /*<<< orphan*/ ,TYPE_1__*) ; 

SCI_REMOTE_DEVICE_HANDLE_T scif_domain_get_device_by_sas_address(
   SCI_DOMAIN_HANDLE_T   domain,
   SCI_SAS_ADDRESS_T   * sas_address
)
{
   SCIF_SAS_DOMAIN_T        * fw_domain = (SCIF_SAS_DOMAIN_T*) domain;
   SCI_ABSTRACT_ELEMENT_T   * element   = sci_abstract_list_get_front(
                                             &fw_domain->remote_device_list
                                          );
   SCIF_SAS_REMOTE_DEVICE_T * fw_device;
   SCI_SAS_ADDRESS_T          fw_device_address;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "scif_domain_get_device_by_sas_address(0x%x, 0x%x) enter\n",
      domain, sas_address
   ));

   // Search the abstract list to see if there is a remote device with the
   // same SAS address.
   while (element != NULL)
   {
      fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                  sci_abstract_list_get_object(element);

      scic_remote_device_get_sas_address(
         fw_device->core_object, &fw_device_address
      );

      // Check to see if this is the device for which we are searching.
      if (  (fw_device_address.low == sas_address->low)
         && (fw_device_address.high == sas_address->high) )
      {
         return fw_device;
      }

      element = sci_abstract_list_get_next(element);
   }

   return SCI_INVALID_HANDLE;
}