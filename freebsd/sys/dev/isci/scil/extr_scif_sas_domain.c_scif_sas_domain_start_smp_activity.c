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
struct TYPE_7__ {int /*<<< orphan*/  scheduled_activity; } ;
struct TYPE_8__ {TYPE_1__ smp_device; } ;
struct TYPE_9__ {TYPE_2__ protocol_device; } ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 TYPE_3__* scif_sas_domain_find_device_has_scheduled_activity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_configure_route_table (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_start_discover (TYPE_3__*) ; 

void scif_sas_domain_start_smp_activity(
  SCIF_SAS_DOMAIN_T        * fw_domain
)
{
   SCIF_SAS_REMOTE_DEVICE_T * device_has_scheduled_activity = NULL;

   //first, find device that has config route table activity scheduled.
   //config route table activity has higher priority than Discover.
   device_has_scheduled_activity =
      scif_sas_domain_find_device_has_scheduled_activity(
         fw_domain,
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE
      );

   if (device_has_scheduled_activity != NULL)
   {
      scif_sas_smp_remote_device_configure_route_table(device_has_scheduled_activity);
      device_has_scheduled_activity->protocol_device.smp_device.scheduled_activity =
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;
      return;
   }

   //if no device has config route table activity scheduled, search again, find
   //device has discover activity scheduled.
   device_has_scheduled_activity =
      scif_sas_domain_find_device_has_scheduled_activity(
         fw_domain,
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER
      );

   if (device_has_scheduled_activity != NULL)
      scif_sas_smp_remote_device_start_discover(device_has_scheduled_activity);
}