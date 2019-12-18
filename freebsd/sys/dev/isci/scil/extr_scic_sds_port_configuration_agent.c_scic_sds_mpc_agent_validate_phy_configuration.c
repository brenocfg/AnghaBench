#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
typedef  int U32 ;
struct TYPE_17__ {TYPE_1__* ports; } ;
struct TYPE_18__ {TYPE_2__ sds1; } ;
struct TYPE_22__ {int /*<<< orphan*/ * phy_table; int /*<<< orphan*/ * port_table; TYPE_3__ oem_parameters; } ;
struct TYPE_21__ {TYPE_4__* phy_valid_port_range; } ;
struct TYPE_20__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_19__ {size_t min_index; size_t max_index; } ;
struct TYPE_16__ {int phy_mask; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_5__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_6__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  TYPE_7__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION ; 
 size_t SCI_MAX_PHYS ; 
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_7__*) ; 
 scalar_t__ sci_sas_address_compare (TYPE_5__,TYPE_5__) ; 
 int /*<<< orphan*/  scic_sds_phy_get_sas_address (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_port_add_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_configuration_agent_validate_ports (TYPE_7__*,TYPE_6__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_mpc_agent_validate_phy_configuration(
   SCIC_SDS_CONTROLLER_T               * controller,
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent
)
{
   U32 phy_mask;
   U32 assigned_phy_mask;
   SCI_SAS_ADDRESS_T sas_address;
   SCI_SAS_ADDRESS_T phy_assigned_address;
   U8 port_index;
   U8 phy_index;

   assigned_phy_mask = 0;
   sas_address.high = 0;
   sas_address.low = 0;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT,
      "scic_sds_mpc_agent_validate_phy_configuration(0x%08x, 0x%08x) enter\n",
      controller, port_agent
   ));

   for (port_index = 0; port_index < SCI_MAX_PORTS; port_index++)
   {
      phy_mask = controller->oem_parameters.sds1.ports[port_index].phy_mask;

      if (phy_mask != 0)
      {
         // Make sure that one or more of the phys were not already assinged to
         // a different port.
         if ((phy_mask & ~assigned_phy_mask) == 0)
         {
            return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
         }

         // Find the starting phy index for this round through the loop
         for (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++)
         {
            if ((1 << phy_index) & phy_mask)
            {
               scic_sds_phy_get_sas_address(
                  &controller->phy_table[phy_index], &sas_address
               );

               // The phy_index can be used as the starting point for the
               // port range since the hardware starts all logical ports
               // the same as the PE index.
               port_agent->phy_valid_port_range[phy_index].min_index = port_index;
               port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

               if (phy_index != port_index)
               {
                  return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
               }

               break;
            }
         }

         // See how many additional phys are being added to this logical port.
         // Note: We have not moved the current phy_index so we will actually
         //       compare the startting phy with itself.
         //       This is expected and required to add the phy to the port.
         while (phy_index < SCI_MAX_PHYS)
         {
            if ((1 << phy_index) & phy_mask)
            {
               scic_sds_phy_get_sas_address(
                  &controller->phy_table[phy_index], &phy_assigned_address
               );

               if (sci_sas_address_compare(sas_address, phy_assigned_address) != 0)
               {
                  // The phy mask specified that this phy is part of the same port
                  // as the starting phy and it is not so fail this configuration
                  return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
               }

               port_agent->phy_valid_port_range[phy_index].min_index = port_index;
               port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

               scic_sds_port_add_phy(
                  &controller->port_table[port_index],
                  &controller->phy_table[phy_index]
               );

               assigned_phy_mask |= (1 << phy_index);
            }

            phy_index++;
         }
      }
   }

   return scic_sds_port_configuration_agent_validate_ports(controller, port_agent);
}