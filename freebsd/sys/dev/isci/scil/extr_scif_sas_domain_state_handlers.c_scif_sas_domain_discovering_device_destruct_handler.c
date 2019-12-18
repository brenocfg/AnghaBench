#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  remote_device_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCI_BASE_DOMAIN_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_abstract_list_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_discovering_device_destruct_handler(
   SCI_BASE_DOMAIN_T        * domain,
   SCI_BASE_REMOTE_DEVICE_T * remote_device
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T *)domain;

   SCIF_LOG_WARNING((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "Domain:0x%x Device:0x%x State:0x%x device destruct in domain DISCOVERING state\n",
      domain, remote_device,
      sci_base_state_machine_get_state(&domain->state_machine)
   ));

   //remove the remote device from domain's remote_device_list
   sci_abstract_list_erase(
      &(fw_domain->remote_device_list),
      remote_device
   );

   return SCI_SUCCESS;
}