#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * phy_table; } ;
struct TYPE_8__ {TYPE_1__* phy_valid_port_range; } ;
struct TYPE_7__ {int max_index; int min_index; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_SAS_ADDRESS_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 scalar_t__ sci_sas_address_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_sas_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_configuration_agent_validate_ports(
   SCIC_SDS_CONTROLLER_T               * controller,
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent
)
{
#if !defined(ARLINGTON_BUILD)
   SCI_SAS_ADDRESS_T first_address;
   SCI_SAS_ADDRESS_T second_address;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT,
      "scic_sds_port_configuration_agent_validate_ports(0x%08x, 0x%08x) enter\n",
      controller, port_agent
   ));

   // Sanity check the max ranges for all the phys the max index
   // is always equal to the port range index
   if (
         (port_agent->phy_valid_port_range[0].max_index != 0)
      || (port_agent->phy_valid_port_range[1].max_index != 1)
      || (port_agent->phy_valid_port_range[2].max_index != 2)
      || (port_agent->phy_valid_port_range[3].max_index != 3)
      )
   {
      return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
   }

   // This is a request to configure a single x4 port or at least attempt
   // to make all the phys into a single port
   if (
         (port_agent->phy_valid_port_range[0].min_index == 0)
      && (port_agent->phy_valid_port_range[1].min_index == 0)
      && (port_agent->phy_valid_port_range[2].min_index == 0)
      && (port_agent->phy_valid_port_range[3].min_index == 0)
      )
   {
      return SCI_SUCCESS;
   }

   // This is a degenerate case where phy 1 and phy 2 are assigned
   // to the same port this is explicitly disallowed by the hardware
   // unless they are part of the same x4 port and this condition was
   // already checked above.
   if (port_agent->phy_valid_port_range[2].min_index == 1)
   {
      return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
   }

   // PE0 and PE3 can never have the same SAS Address unless they
   // are part of the same x4 wide port and we have already checked
   // for this condition.
   scic_sds_phy_get_sas_address(&controller->phy_table[0], &first_address);
   scic_sds_phy_get_sas_address(&controller->phy_table[3], &second_address);

   if (sci_sas_address_compare(first_address, second_address) == 0)
   {
      return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
   }

   // PE0 and PE1 are configured into a 2x1 ports make sure that the
   // SAS Address for PE0 and PE2 are different since they can not be
   // part of the same port.
   if (
         (port_agent->phy_valid_port_range[0].min_index == 0)
      && (port_agent->phy_valid_port_range[1].min_index == 1)
      )
   {
      scic_sds_phy_get_sas_address(&controller->phy_table[0], &first_address);
      scic_sds_phy_get_sas_address(&controller->phy_table[2], &second_address);

      if (sci_sas_address_compare(first_address, second_address) == 0)
      {
         return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
      }
   }

   // PE2 and PE3 are configured into a 2x1 ports make sure that the
   // SAS Address for PE1 and PE3 are different since they can not be
   // part of the same port.
   if (
         (port_agent->phy_valid_port_range[2].min_index == 2)
      && (port_agent->phy_valid_port_range[3].min_index == 3)
      )
   {
      scic_sds_phy_get_sas_address(&controller->phy_table[1], &first_address);
      scic_sds_phy_get_sas_address(&controller->phy_table[3], &second_address);

      if (sci_sas_address_compare(first_address, second_address) == 0)
      {
         return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
      }
   }
#endif // !defined(ARLINGTON_BUILD)

   return SCI_SUCCESS;
}