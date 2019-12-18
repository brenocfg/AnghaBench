#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t U16 ;
struct TYPE_23__ {int stp_inactivity_timeout; int ssp_inactivity_timeout; int stp_max_occupancy_timeout; int ssp_max_occupancy_timeout; int no_outbound_task_timeout; TYPE_3__* phys; } ;
struct TYPE_15__ {int max_number_concurrent_device_spin_up; scalar_t__ cable_selection_mask; scalar_t__ ssc_sas_tx_type; scalar_t__ ssc_sas_tx_spread_level; scalar_t__ ssc_sata_tx_spread_level; int /*<<< orphan*/  mode_type; } ;
struct TYPE_21__ {TYPE_6__* phys; TYPE_2__* ports; TYPE_1__ controller; } ;
struct TYPE_22__ {TYPE_7__ sds1; } ;
struct TYPE_18__ {int high; scalar_t__ low; } ;
struct TYPE_19__ {TYPE_4__ sci_format; } ;
struct TYPE_20__ {int afe_tx_amp_control0; int afe_tx_amp_control1; int afe_tx_amp_control2; int afe_tx_amp_control3; TYPE_5__ sas_address; } ;
struct TYPE_17__ {int max_speed_generation; int align_insertion_frequency; int in_connection_align_insertion_frequency; int notify_enable_spin_up_insertion_frequency; } ;
struct TYPE_16__ {scalar_t__ phy_mask; } ;
struct TYPE_13__ {TYPE_9__ sds1; } ;
struct TYPE_14__ {scalar_t__ pci_revision; TYPE_10__ user_parameters; TYPE_8__ oem_parameters; scalar_t__ controller_index; } ;
typedef  TYPE_11__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_SDS_PCI_REVISION_A0 ; 
 scalar_t__ SCIC_SDS_PCI_REVISION_A2 ; 
 scalar_t__ SCIC_SDS_PCI_REVISION_B0 ; 
 size_t SCI_MAX_PHYS ; 
 size_t SCI_MAX_PORTS ; 

__attribute__((used)) static
void scic_sds_controller_set_default_config_parameters(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U16 index;

   // Default to APC mode.
   this_controller->oem_parameters.sds1.controller.mode_type = SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE;

   // Default to 1
   this_controller->oem_parameters.sds1.controller.max_number_concurrent_device_spin_up = 1;

   // Default to no SSC operation.
   this_controller->oem_parameters.sds1.controller.ssc_sata_tx_spread_level = 0;
   this_controller->oem_parameters.sds1.controller.ssc_sas_tx_spread_level  = 0;
   this_controller->oem_parameters.sds1.controller.ssc_sas_tx_type          = 0;

   // Default to all phys to using short cables
   this_controller->oem_parameters.sds1.controller.cable_selection_mask = 0;

   // Initialize all of the port parameter information to narrow ports.
   for (index = 0; index < SCI_MAX_PORTS; index++)
   {
      this_controller->oem_parameters.sds1.ports[index].phy_mask = 0;
   }

   // Initialize all of the phy parameter information.
   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      // Default to 6G (i.e. Gen 3) for now.  User can override if
      // they choose.
      this_controller->user_parameters.sds1.phys[index].max_speed_generation = 2;

      //the frequencies cannot be 0
      this_controller->user_parameters.sds1.phys[index].align_insertion_frequency = 0x7f;
      this_controller->user_parameters.sds1.phys[index].in_connection_align_insertion_frequency = 0xff;
      this_controller->user_parameters.sds1.phys[index].notify_enable_spin_up_insertion_frequency = 0x33;

      // Previous Vitesse based expanders had a arbitration issue that
      // is worked around by having the upper 32-bits of SAS address
      // with a value greater then the Vitesse company identifier.
      // Hence, usage of 0x5FCFFFFF.
      this_controller->oem_parameters.sds1.phys[index].sas_address.sci_format.high
         = 0x5FCFFFFF;

      // Add in controller index to ensure each controller will have unique SAS addresses by default.
      this_controller->oem_parameters.sds1.phys[index].sas_address.sci_format.low
         = 0x00000001 + this_controller->controller_index;

      if (  (this_controller->pci_revision == SCIC_SDS_PCI_REVISION_A0)
         || (this_controller->pci_revision == SCIC_SDS_PCI_REVISION_A2)
         || (this_controller->pci_revision == SCIC_SDS_PCI_REVISION_B0) )
      {
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control0 = 0x000E7C03;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control1 = 0x000E7C03;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control2 = 0x000E7C03;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control3 = 0x000E7C03;
      }
      else // This must be SCIC_SDS_PCI_REVISION_C0
      {
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control0 = 0x000BDD08;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control1 = 0x000B7069;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control2 = 0x000B7C09;
         this_controller->oem_parameters.sds1.phys[index].afe_tx_amp_control3 = 0x000AFC6E;
      }
   }

   this_controller->user_parameters.sds1.stp_inactivity_timeout = 5;
   this_controller->user_parameters.sds1.ssp_inactivity_timeout = 5;
   this_controller->user_parameters.sds1.stp_max_occupancy_timeout = 5;
   this_controller->user_parameters.sds1.ssp_max_occupancy_timeout = 20;
   this_controller->user_parameters.sds1.no_outbound_task_timeout = 20;

}