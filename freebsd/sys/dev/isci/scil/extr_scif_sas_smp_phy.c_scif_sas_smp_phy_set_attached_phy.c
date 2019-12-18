#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_7__ {int /*<<< orphan*/  smp_device; } ;
struct TYPE_10__ {TYPE_1__ protocol_device; } ;
struct TYPE_8__ {TYPE_3__* attached_phy; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_3__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ scif_sas_smp_remote_device_find_smp_phy_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_smp_phy_set_attached_phy(
   SCIF_SAS_SMP_PHY_T       * this_smp_phy,
   U8                         attached_phy_identifier,
   SCIF_SAS_REMOTE_DEVICE_T * attached_remote_device
)
{
   //find the attached phy from its owning device by attached_phy_id.
   SCIF_SAS_SMP_PHY_T * attached_smp_phy =
      (SCIF_SAS_SMP_PHY_T *)scif_sas_smp_remote_device_find_smp_phy_by_id(
          attached_phy_identifier,
          &attached_remote_device->protocol_device.smp_device);

   if (attached_smp_phy != NULL)
   {
      this_smp_phy->u.attached_phy = attached_smp_phy;
      attached_smp_phy->u.attached_phy = this_smp_phy;

      return SCI_SUCCESS;
   }

   return SCI_FAILURE;
}