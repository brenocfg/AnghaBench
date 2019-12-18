#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * smp_activity_timer; int /*<<< orphan*/ * curr_clear_affiliation_phy; scalar_t__ io_retry_count; void* scheduled_activity; int /*<<< orphan*/ * curr_config_route_destination_smp_phy; int /*<<< orphan*/  is_route_table_cleaned; int /*<<< orphan*/ * config_route_smp_phy_anchor; scalar_t__ curr_config_route_index; scalar_t__ current_activity_phy_index; int /*<<< orphan*/  current_smp_request; void* current_activity; } ;
struct TYPE_8__ {TYPE_2__ smp_device; } ;
struct TYPE_9__ {TYPE_3__ protocol_device; TYPE_1__* domain; } ;
struct TYPE_6__ {int /*<<< orphan*/  controller; } ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NOT_IN_SMP_ACTIVITY ; 
 void* SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 int /*<<< orphan*/  scif_cb_timer_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cb_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void scif_sas_smp_remote_device_clear(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   //reset all fields in smp_device, indicate that the smp device is not
   //in discovery process.
   fw_device->protocol_device.smp_device.current_activity =
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

   fw_device->protocol_device.smp_device.current_smp_request =
      NOT_IN_SMP_ACTIVITY;

   fw_device->protocol_device.smp_device.current_activity_phy_index = 0;

   fw_device->protocol_device.smp_device.curr_config_route_index = 0;

   fw_device->protocol_device.smp_device.config_route_smp_phy_anchor = NULL;

   fw_device->protocol_device.smp_device.is_route_table_cleaned = FALSE;

   fw_device->protocol_device.smp_device.curr_config_route_destination_smp_phy = NULL;

   fw_device->protocol_device.smp_device.scheduled_activity =
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

   fw_device->protocol_device.smp_device.io_retry_count = 0;

   fw_device->protocol_device.smp_device.curr_clear_affiliation_phy = NULL;

   if (fw_device->protocol_device.smp_device.smp_activity_timer != NULL)
   {
      //stop the timer
      scif_cb_timer_stop(
         fw_device->domain->controller,
         fw_device->protocol_device.smp_device.smp_activity_timer
      );

      //destroy the timer
      scif_cb_timer_destroy(
         fw_device->domain->controller,
         fw_device->protocol_device.smp_device.smp_activity_timer
      );

      fw_device->protocol_device.smp_device.smp_activity_timer = NULL;
   }
}