#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  size_t U16 ;
struct TYPE_28__ {scalar_t__ mode_type; scalar_t__ max_number_concurrent_device_spin_up; } ;
struct TYPE_30__ {TYPE_7__ controller; TYPE_6__* ports; TYPE_5__* phys; } ;
struct TYPE_29__ {int do_enable_ssc; } ;
struct TYPE_27__ {scalar_t__ phy_mask; } ;
struct TYPE_24__ {scalar_t__ high; scalar_t__ low; } ;
struct TYPE_25__ {TYPE_3__ sci_format; } ;
struct TYPE_26__ {scalar_t__ afe_tx_amp_control0; scalar_t__ afe_tx_amp_control1; scalar_t__ afe_tx_amp_control2; scalar_t__ afe_tx_amp_control3; TYPE_4__ sas_address; } ;
struct TYPE_22__ {scalar_t__ current_state_id; } ;
struct TYPE_23__ {TYPE_1__ state_machine; } ;
struct TYPE_21__ {TYPE_9__ sds1; } ;
struct TYPE_20__ {int /*<<< orphan*/  oem_parameters; scalar_t__ oem_parameters_version; TYPE_2__ parent; } ;
struct TYPE_19__ {TYPE_8__ controller; } ;
struct TYPE_17__ {scalar_t__ ssc_sata_tx_spread_level; scalar_t__ ssc_sas_tx_spread_level; int ssc_sas_tx_type; } ;
struct TYPE_18__ {TYPE_10__ controller; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_11__ SCI_BIOS_OEM_PARAM_ELEMENT_v_1_1_T ;
typedef  TYPE_12__ SCI_BIOS_OEM_PARAM_ELEMENT_T ;
typedef  TYPE_13__ SCIC_SDS_CONTROLLER_T ;
typedef  TYPE_14__ SCIC_OEM_PARAMETERS_T ;

/* Variables and functions */
 scalar_t__ MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT ; 
 scalar_t__ SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_PORT_MANUAL_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_SDS_PARM_PHY_MASK_MAX ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZING ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_RESET ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 size_t SCI_MAX_PHYS ; 
 size_t SCI_MAX_PORTS ; 
 scalar_t__ SCI_OEM_PARAM_VER_1_0 ; 
 scalar_t__ SCI_OEM_PARAM_VER_1_1 ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_14__*,int) ; 

SCI_STATUS scic_oem_parameters_set(
   SCI_CONTROLLER_HANDLE_T   controller,
   SCIC_OEM_PARAMETERS_T   * scic_parms,
   U8 scic_parms_version
)
{
   SCIC_SDS_CONTROLLER_T * this_controller = (SCIC_SDS_CONTROLLER_T*)controller;
   SCI_BIOS_OEM_PARAM_ELEMENT_T *old_oem_params =
                (SCI_BIOS_OEM_PARAM_ELEMENT_T *)(&(scic_parms->sds1));


   if (
         (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_RESET)
      || (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZING)
      || (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZED)
      )
   {
      U16  index;
      U8   combined_phy_mask = 0;

      /*
       * Set the OEM parameter version for the controller. This comes
       * from the OEM parameter block header or the registry depending
       * on what WCDL is set to retrieve.
       */
      this_controller->oem_parameters_version = scic_parms_version;

      // Validate the oem parameters.  If they are not legal, then
      // return a failure.
      for(index=0; index<SCI_MAX_PORTS; index++)
      {
         if (scic_parms->sds1.ports[index].phy_mask > SCIC_SDS_PARM_PHY_MASK_MAX)
         {
            return SCI_FAILURE_INVALID_PARAMETER_VALUE;
         }
      }

      for(index=0; index<SCI_MAX_PHYS; index++)
      {
         if (
             scic_parms->sds1.phys[index].sas_address.sci_format.high == 0
                 && scic_parms->sds1.phys[index].sas_address.sci_format.low  == 0
        )
        {
            return SCI_FAILURE_INVALID_PARAMETER_VALUE;
        }

#if defined(PBG_HBA_A0_BUILD) || defined(PBG_HBA_A2_BUILD) || defined(PBG_HBA_BETA_BUILD) || defined(PBG_BUILD)
        if (
              (scic_parms->sds1.phys[index].afe_tx_amp_control0 == 0) ||
              (scic_parms->sds1.phys[index].afe_tx_amp_control1 == 0) ||
              (scic_parms->sds1.phys[index].afe_tx_amp_control2 == 0) ||
              (scic_parms->sds1.phys[index].afe_tx_amp_control3 == 0)
              )
        {
           return SCI_FAILURE_INVALID_PARAMETER_VALUE;
        }
#endif
      }

      if (scic_parms->sds1.controller.mode_type == SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE)
      {
         for(index=0; index<SCI_MAX_PHYS; index++)
         {
            if (scic_parms->sds1.ports[index].phy_mask != 0)
            {
               return SCI_FAILURE_INVALID_PARAMETER_VALUE;
            }
         }
      }
      else if (scic_parms->sds1.controller.mode_type == SCIC_PORT_MANUAL_CONFIGURATION_MODE)
      {
         for(index=0; index<SCI_MAX_PHYS; index++)
         {
            combined_phy_mask |= scic_parms->sds1.ports[index].phy_mask;
         }

         if (combined_phy_mask == 0)
         {
            return SCI_FAILURE_INVALID_PARAMETER_VALUE;
         }
      }
      else
      {
         return SCI_FAILURE_INVALID_PARAMETER_VALUE;
      }

      if (scic_parms->sds1.controller.max_number_concurrent_device_spin_up > MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT)
      {
         return SCI_FAILURE_INVALID_PARAMETER_VALUE;
      }

      if (old_oem_params->controller.do_enable_ssc != 0)
      {
         if (  (scic_parms_version == SCI_OEM_PARAM_VER_1_0)
            && (old_oem_params->controller.do_enable_ssc != 0x01))
             return SCI_FAILURE_INVALID_PARAMETER_VALUE;

         if (scic_parms_version >= SCI_OEM_PARAM_VER_1_1)
         {
            SCI_BIOS_OEM_PARAM_ELEMENT_v_1_1_T *oem_params =
                (SCI_BIOS_OEM_PARAM_ELEMENT_v_1_1_T*)(&(scic_parms->sds1));

            U8 test = oem_params->controller.ssc_sata_tx_spread_level;
            if ( !((test == 0x0) || (test == 0x2) || (test == 0x3) ||
                 (test == 0x6) || (test == 0x7)) )
                return SCI_FAILURE_INVALID_PARAMETER_VALUE;

            test = oem_params->controller.ssc_sas_tx_spread_level;
            if (oem_params->controller.ssc_sas_tx_type == 0)
            {
                if ( !((test == 0x0) || (test == 0x2) || (test == 0x3)) )
                    return SCI_FAILURE_INVALID_PARAMETER_VALUE;
            }
            else
            if (oem_params->controller.ssc_sas_tx_type == 1)
            {
                if ( !((test == 0x0) || (test == 0x3) || (test == 0x6)) )
                    return SCI_FAILURE_INVALID_PARAMETER_VALUE;
            }
         }
      }

      memcpy(
         (&this_controller->oem_parameters), scic_parms, sizeof(*scic_parms));
      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INVALID_STATE;
}