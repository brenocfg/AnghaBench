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
struct TYPE_4__ {scalar_t__ high; scalar_t__ low; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCI_SAS_ADDRESS_T ;
typedef  int /*<<< orphan*/  SCI_BASE_PORT_T ;
typedef  int /*<<< orphan*/  SCI_BASE_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION ; 
 int /*<<< orphan*/  scic_sds_phy_get_sas_address (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_sas_address (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_set_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_stopped_state_add_phy_handler(
   SCI_BASE_PORT_T *port,
   SCI_BASE_PHY_T  *phy
)
{
   SCIC_SDS_PORT_T * this_port = (SCIC_SDS_PORT_T *)port;
   SCIC_SDS_PHY_T  * this_phy  = (SCIC_SDS_PHY_T  *)phy;
   SCI_SAS_ADDRESS_T port_sas_address;

   // Read the port assigned SAS Address if there is one
   scic_sds_port_get_sas_address(this_port, &port_sas_address);

   if (port_sas_address.high != 0 && port_sas_address.low != 0)
   {
      SCI_SAS_ADDRESS_T phy_sas_address;

      // Make sure that the PHY SAS Address matches the SAS Address
      // for this port.
      scic_sds_phy_get_sas_address(this_phy, &phy_sas_address);

      if (
            (port_sas_address.high != phy_sas_address.high)
         || (port_sas_address.low  != phy_sas_address.low)
         )
      {
         return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
      }
   }

   return scic_sds_port_set_phy(this_port, this_phy);
}