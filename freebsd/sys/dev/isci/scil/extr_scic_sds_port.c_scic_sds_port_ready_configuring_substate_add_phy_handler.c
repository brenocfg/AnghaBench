#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ready_substate_machine; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_PORT_T ;
typedef  int /*<<< orphan*/  SCI_BASE_PHY_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_CONFIGURING ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_general_link_up_handler (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_port_set_phy (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_ready_configuring_substate_add_phy_handler(
   SCI_BASE_PORT_T *port,
   SCI_BASE_PHY_T  *phy
)
{
   SCIC_SDS_PORT_T * this_port = (SCIC_SDS_PORT_T *)port;
   SCIC_SDS_PHY_T  * this_phy  = (SCIC_SDS_PHY_T  *)phy;
   SCI_STATUS        status;

   status = scic_sds_port_set_phy(this_port, this_phy);

   if (status == SCI_SUCCESS)
   {
      scic_sds_port_general_link_up_handler(this_port, this_phy, TRUE, FALSE);

      // Re-enter the configuring state since this may be the last phy in
      // the port.
      sci_base_state_machine_change_state(
         &this_port->ready_substate_machine,
         SCIC_SDS_PORT_READY_SUBSTATE_CONFIGURING
      );
   }

   return status;
}