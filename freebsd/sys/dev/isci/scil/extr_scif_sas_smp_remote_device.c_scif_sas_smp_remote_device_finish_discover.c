#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ is_config_route_table_needed; } ;
struct TYPE_12__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_13__ {TYPE_1__ smp_phy_list; } ;
struct TYPE_14__ {TYPE_2__ smp_device; } ;
struct TYPE_15__ {TYPE_3__ protocol_device; TYPE_5__* domain; } ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_5__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_domain_continue_discover (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_clear (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_configure_upstream_expander_route_info (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_print_smp_phy_list (TYPE_4__*) ; 

void scif_sas_smp_remote_device_finish_discover(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = fw_device->domain;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_finish_discover(0x%x) enter\n",
      fw_device
   ));

   if ( fw_domain->is_config_route_table_needed
       && fw_device->protocol_device.smp_device.smp_phy_list.list_head != NULL)
      scif_sas_smp_remote_device_configure_upstream_expander_route_info(fw_device);

   //call the common private routine to reset all fields of this smp device.
   scif_sas_smp_remote_device_clear(fw_device);

#ifdef SCI_SMP_PHY_LIST_DEBUG_PRINT
   scif_sas_smp_remote_device_print_smp_phy_list(fw_device);
#endif

   //notify domain this smp device's discover finishes, it's up to domain
   //to continue the discover process in a bigger scope.
   scif_sas_domain_continue_discover(fw_domain);
}