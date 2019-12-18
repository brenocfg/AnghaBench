#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__* curr_clear_affiliation_phy; } ;
struct TYPE_13__ {TYPE_5__ smp_device; } ;
struct TYPE_18__ {TYPE_1__* domain; TYPE_2__ protocol_device; } ;
struct TYPE_15__ {TYPE_3__* next; } ;
struct TYPE_17__ {int /*<<< orphan*/  phy_identifier; TYPE_4__ list_element; } ;
struct TYPE_14__ {int /*<<< orphan*/  object; } ;
struct TYPE_12__ {int /*<<< orphan*/  controller; } ;
typedef  TYPE_5__ SCIF_SAS_SMP_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_OPERATION_CLEAR_AFFILIATION ; 
 TYPE_6__* scif_sas_smp_remote_device_find_next_smp_phy_link_to_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_finish_clear_affiliation (TYPE_7__*) ; 
 int /*<<< orphan*/  scif_sas_smp_request_construct_phy_control (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_sas_smp_remote_device_continue_clear_affiliation(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_SMP_REMOTE_DEVICE_T * smp_device =
      &fw_device->protocol_device.smp_device;

   //search from next immediate smp phy.
   SCIF_SAS_SMP_PHY_T * phy_to_clear_affiliation = NULL;

   if (smp_device->curr_clear_affiliation_phy->list_element.next != NULL)
   {
      phy_to_clear_affiliation =
         scif_sas_smp_remote_device_find_next_smp_phy_link_to_sata(
            smp_device->curr_clear_affiliation_phy->list_element.next->object
         );
   }

   if (phy_to_clear_affiliation != NULL)
   {
      smp_device->curr_clear_affiliation_phy = phy_to_clear_affiliation;

      //build PHY Control (clear affiliation) to the phy.
      scif_sas_smp_request_construct_phy_control(
         fw_device->domain->controller,
         fw_device,
         PHY_OPERATION_CLEAR_AFFILIATION,
         phy_to_clear_affiliation->phy_identifier,
         NULL,
         NULL
      );
   }
   else
      scif_sas_smp_remote_device_finish_clear_affiliation(fw_device);
}