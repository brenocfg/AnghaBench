#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_11__ {TYPE_1__ sas_address; } ;
struct TYPE_12__ {TYPE_2__ identify_address_frame_buffer; } ;
struct TYPE_13__ {TYPE_3__ sas; } ;
struct TYPE_15__ {TYPE_4__ phy_type; } ;
struct TYPE_14__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
typedef  TYPE_5__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_6__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 

void scic_sds_phy_get_attached_sas_address(
   SCIC_SDS_PHY_T    *this_phy,
   SCI_SAS_ADDRESS_T *sas_address
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sds_phy_get_attached_sas_address(0x%x, 0x%x) enter\n",
      this_phy, sas_address
   ));

   sas_address->high
      = this_phy->phy_type.sas.identify_address_frame_buffer.sas_address.high;
   sas_address->low
      = this_phy->phy_type.sas.identify_address_frame_buffer.sas_address.low;
}