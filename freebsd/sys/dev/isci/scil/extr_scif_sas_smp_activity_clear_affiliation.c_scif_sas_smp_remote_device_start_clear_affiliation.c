#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* list_head; } ;
struct TYPE_17__ {int /*<<< orphan*/  scheduled_activity; int /*<<< orphan*/  current_smp_request; int /*<<< orphan*/  current_activity; TYPE_6__* curr_clear_affiliation_phy; TYPE_2__ smp_phy_list; } ;
struct TYPE_15__ {TYPE_5__ smp_device; } ;
struct TYPE_19__ {TYPE_4__* domain; TYPE_3__ protocol_device; } ;
struct TYPE_18__ {int /*<<< orphan*/  phy_identifier; } ;
struct TYPE_16__ {int /*<<< orphan*/  controller; } ;
struct TYPE_13__ {scalar_t__ object; } ;
typedef  TYPE_5__ SCIF_SAS_SMP_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_OPERATION_CLEAR_AFFILIATION ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 int /*<<< orphan*/  SMP_FUNCTION_PHY_CONTROL ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_start_high_priority_io ; 
 TYPE_6__* scif_sas_smp_remote_device_find_next_smp_phy_link_to_sata (TYPE_6__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_finish_clear_affiliation (TYPE_7__*) ; 
 int /*<<< orphan*/  scif_sas_smp_request_construct_phy_control (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_sas_smp_remote_device_start_clear_affiliation(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_SMP_REMOTE_DEVICE_T * smp_device =
      &fw_device->protocol_device.smp_device;

   SCIF_SAS_SMP_PHY_T * phy_to_clear_affiliation = NULL;

   if (smp_device->smp_phy_list.list_head != NULL)
   {
      phy_to_clear_affiliation =
         scif_sas_smp_remote_device_find_next_smp_phy_link_to_sata(
            (SCIF_SAS_SMP_PHY_T *)smp_device->smp_phy_list.list_head->object
         );
   }

   if (phy_to_clear_affiliation != NULL)
   {
      smp_device->curr_clear_affiliation_phy = phy_to_clear_affiliation;

      //set current activity
      fw_device->protocol_device.smp_device.current_activity =
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION;

      //Set current_smp_request to PHY CONTROL.
      fw_device->protocol_device.smp_device.current_smp_request =
         SMP_FUNCTION_PHY_CONTROL;

      //reset discover_to_start flag.
      fw_device->protocol_device.smp_device.scheduled_activity =
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

      //build PHY Control (clear affiliation) to the phy.
      scif_sas_smp_request_construct_phy_control(
         fw_device->domain->controller,
         fw_device,
         PHY_OPERATION_CLEAR_AFFILIATION,
         phy_to_clear_affiliation->phy_identifier,
         NULL,
         NULL
      );

      //issue DPC to start this request.
      scif_cb_start_internal_io_task_schedule(
         fw_device->domain->controller,
         scif_sas_controller_start_high_priority_io,
         fw_device->domain->controller
      );
   }
   else
      scif_sas_smp_remote_device_finish_clear_affiliation(fw_device);
}