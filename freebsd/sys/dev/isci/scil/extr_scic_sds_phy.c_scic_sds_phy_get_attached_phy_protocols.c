#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ all; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
struct TYPE_15__ {TYPE_2__ protocols; } ;
struct TYPE_16__ {TYPE_3__ identify_address_frame_buffer; } ;
struct TYPE_17__ {TYPE_4__ sas; } ;
struct TYPE_21__ {scalar_t__ protocol; TYPE_5__ phy_type; } ;
struct TYPE_18__ {int stp_target; } ;
struct TYPE_19__ {TYPE_6__ bits; scalar_t__ all; } ;
struct TYPE_20__ {TYPE_7__ u; } ;
typedef  TYPE_8__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  TYPE_9__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SAS ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SATA ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_9__*) ; 

void scic_sds_phy_get_attached_phy_protocols(
   SCIC_SDS_PHY_T *this_phy,
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T * protocols
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sds_phy_get_attached_phy_protocols(this_phy:0x%x, protocols:0x%x[0x%x])\n",
      this_phy, protocols, protocols->u.all
   ));

   protocols->u.all = 0;

   if (this_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SAS)
   {
      protocols->u.all =
         this_phy->phy_type.sas.identify_address_frame_buffer.protocols.u.all;
   }
   else if (this_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SATA)
   {
      protocols->u.bits.stp_target = 1;
   }
}