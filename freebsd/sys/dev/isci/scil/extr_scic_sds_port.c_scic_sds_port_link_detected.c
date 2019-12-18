#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {size_t phy_index; } ;
struct TYPE_19__ {scalar_t__ logical_port_index; TYPE_3__* owning_controller; } ;
struct TYPE_15__ {scalar_t__ stp_target; } ;
struct TYPE_16__ {TYPE_1__ bits; } ;
struct TYPE_18__ {TYPE_2__ u; } ;
struct TYPE_17__ {TYPE_5__* port_table; } ;
typedef  TYPE_4__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  TYPE_5__ SCIC_SDS_PORT_T ;
typedef  TYPE_6__ SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCIC_SDS_DUMMY_PORT ; 
 int /*<<< orphan*/  SCU_PCSPExCR_WRITE (TYPE_5__*,size_t,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_sds_phy_get_attached_phy_protocols (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_port_invalid_link_up (TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ scic_sds_port_is_wide (TYPE_5__*) ; 

BOOL scic_sds_port_link_detected(
   SCIC_SDS_PORT_T *this_port,
   SCIC_SDS_PHY_T  *the_phy
)
{
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T protocols;

   scic_sds_phy_get_attached_phy_protocols(the_phy, &protocols);

   if (
         (this_port->logical_port_index != SCIC_SDS_DUMMY_PORT)
      && (protocols.u.bits.stp_target)
      )
   {
      if (scic_sds_port_is_wide(this_port))
      {
         //direct attached Sata phy cannot be in wide port.
         scic_sds_port_invalid_link_up( this_port, the_phy);
      return FALSE;
   }
      else
      {
         SCIC_SDS_PORT_T *destination_port = &(this_port->owning_controller->port_table[the_phy->phy_index]);

         //add the phy to the its logical port for direct attached SATA. The phy will be added
         //to port whose port_index will be the phy_index.
         SCU_PCSPExCR_WRITE( destination_port, the_phy->phy_index, the_phy->phy_index);
      }
   }

   return TRUE;
}