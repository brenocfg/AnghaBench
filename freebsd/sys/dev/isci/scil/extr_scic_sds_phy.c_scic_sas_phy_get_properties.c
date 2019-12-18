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
struct TYPE_13__ {int /*<<< orphan*/  all; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct TYPE_15__ {TYPE_1__ received_capabilities; int /*<<< orphan*/  received_iaf; } ;
struct TYPE_11__ {int /*<<< orphan*/  identify_address_frame_buffer; } ;
struct TYPE_12__ {TYPE_2__ sas; } ;
struct TYPE_14__ {scalar_t__ protocol; TYPE_3__ phy_type; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_SAS_IDENTIFY_ADDRESS_FRAME_T ;
typedef  scalar_t__ SCI_PHY_HANDLE_T ;
typedef  TYPE_5__ SCIC_SDS_PHY_T ;
typedef  TYPE_6__ SCIC_SAS_PHY_PROPERTIES_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SAS ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_SAS_RECPHYCAP_READ (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 

SCI_STATUS scic_sas_phy_get_properties(
   SCI_PHY_HANDLE_T            phy,
   SCIC_SAS_PHY_PROPERTIES_T * properties
)
{
   SCIC_SDS_PHY_T *this_phy;
   this_phy = (SCIC_SDS_PHY_T *)phy;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sas_phy_get_properties(0x%x, 0x%x) enter\n",
      this_phy, properties
   ));

   if (this_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SAS)
   {
      memcpy(
         &properties->received_iaf,
         &this_phy->phy_type.sas.identify_address_frame_buffer,
         sizeof(SCI_SAS_IDENTIFY_ADDRESS_FRAME_T)
      );

      properties->received_capabilities.u.all
         = SCU_SAS_RECPHYCAP_READ(this_phy);

      return SCI_SUCCESS;
   }

   return SCI_FAILURE;
}