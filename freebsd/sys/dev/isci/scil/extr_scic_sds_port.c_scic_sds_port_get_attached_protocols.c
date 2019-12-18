#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ all; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_get_attached_phy_protocols (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * scic_sds_port_get_a_connected_phy (int /*<<< orphan*/ *) ; 

void scic_sds_port_get_attached_protocols(
   SCIC_SDS_PORT_T                            * this_port,
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T * protocols
)
{
   SCIC_SDS_PHY_T  *phy;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "scic_sds_port_get_attached_protocols(0x%x, 0x%x) enter\n",
      this_port, protocols
   ));

   // Ensure that the phy is both part of the port and currently
   // connected to the remote end-point.
   phy = scic_sds_port_get_a_connected_phy(this_port);
   if (phy != NULL)
      scic_sds_phy_get_attached_phy_protocols(phy, protocols);
   else
      protocols->u.all = 0;
}