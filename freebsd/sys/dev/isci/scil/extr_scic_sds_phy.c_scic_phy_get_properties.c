#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
struct TYPE_33__ {TYPE_8__* phys; } ;
struct TYPE_30__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_31__ {TYPE_6__ sci_format; } ;
struct TYPE_32__ {TYPE_7__ sas_address; } ;
struct TYPE_28__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_29__ {TYPE_4__ sas_address; int /*<<< orphan*/  protocols; } ;
struct TYPE_26__ {TYPE_1__* phys; } ;
struct TYPE_27__ {TYPE_2__ sds1; } ;
struct TYPE_25__ {scalar_t__ max_speed_generation; } ;
struct TYPE_24__ {size_t index; TYPE_5__ transmit_iaf; int /*<<< orphan*/  owning_port; int /*<<< orphan*/  max_link_rate; int /*<<< orphan*/  negotiated_link_rate; } ;
struct TYPE_23__ {size_t phy_index; TYPE_12__* owning_port; int /*<<< orphan*/  max_negotiated_speed; } ;
struct TYPE_22__ {TYPE_11__* owning_controller; } ;
struct TYPE_20__ {TYPE_9__ sds1; } ;
struct TYPE_21__ {TYPE_10__ oem_parameters; TYPE_3__ user_parameters; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_PHY_HANDLE_T ;
typedef  TYPE_13__ SCIC_SDS_PHY_T ;
typedef  TYPE_14__ SCIC_PHY_PROPERTIES_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIC_SDS_PARM_GEN2_SPEED ; 
 scalar_t__ SCIC_SDS_PARM_GEN3_SPEED ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PHY ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  SCI_SAS_150_GB ; 
 int /*<<< orphan*/  SCI_SAS_300_GB ; 
 int /*<<< orphan*/  SCI_SAS_600_GB ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_13__*) ; 
 int /*<<< orphan*/  scic_sds_phy_get_port (TYPE_13__*) ; 
 int /*<<< orphan*/  scic_sds_phy_get_protocols (TYPE_13__*,int /*<<< orphan*/ *) ; 

SCI_STATUS scic_phy_get_properties(
   SCI_PHY_HANDLE_T        phy,
   SCIC_PHY_PROPERTIES_T * properties
)
{
   SCIC_SDS_PHY_T *this_phy;
   U8 max_speed_generation;

   this_phy = (SCIC_SDS_PHY_T *)phy;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_phy_get_properties(0x%x, 0x%x) enter\n",
      this_phy, properties
   ));

   if (phy == SCI_INVALID_HANDLE)
   {
      return SCI_FAILURE_INVALID_PHY;
   }

   memset(properties, 0, sizeof(SCIC_PHY_PROPERTIES_T));

   //get max link rate of this phy set by user.
   max_speed_generation =
      this_phy->owning_port->owning_controller->user_parameters.sds1.
         phys[this_phy->phy_index].max_speed_generation;

   properties->negotiated_link_rate     = this_phy->max_negotiated_speed;

   if (max_speed_generation == SCIC_SDS_PARM_GEN3_SPEED)
      properties->max_link_rate            = SCI_SAS_600_GB;
   else if (max_speed_generation == SCIC_SDS_PARM_GEN2_SPEED)
      properties->max_link_rate            = SCI_SAS_300_GB;
   else
      properties->max_link_rate            = SCI_SAS_150_GB;

   properties->index                    = this_phy->phy_index;
   properties->owning_port              = scic_sds_phy_get_port(this_phy);

   scic_sds_phy_get_protocols(this_phy, &properties->transmit_iaf.protocols);

   properties->transmit_iaf.sas_address.high =
      this_phy->owning_port->owning_controller->oem_parameters.sds1.
         phys[this_phy->phy_index].sas_address.sci_format.high;

   properties->transmit_iaf.sas_address.low =
      this_phy->owning_port->owning_controller->oem_parameters.sds1.
         phys[this_phy->phy_index].sas_address.sci_format.low;

   return SCI_SUCCESS;
}