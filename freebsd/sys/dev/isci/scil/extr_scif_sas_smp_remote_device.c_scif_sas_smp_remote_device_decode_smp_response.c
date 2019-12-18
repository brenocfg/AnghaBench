#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int current_smp_request; int /*<<< orphan*/  current_activity; int /*<<< orphan*/ * smp_activity_timer; } ;
struct TYPE_17__ {TYPE_2__ smp_device; } ;
struct TYPE_18__ {TYPE_3__ protocol_device; TYPE_1__* domain; } ;
struct TYPE_15__ {int /*<<< orphan*/  controller; } ;
typedef  int /*<<< orphan*/  SMP_RESPONSE_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_IO_STATUS ;
typedef  int /*<<< orphan*/  SCIF_SAS_REQUEST_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_SATA_SPINUP_HOLD_RELEASE ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET ; 
 scalar_t__ SCI_FAILURE_RETRY_REQUIRED ; 
 scalar_t__ SCI_FAILURE_UNSUPPORTED_INFORMATION_TYPE ; 
 scalar_t__ SCI_SUCCESS ; 
#define  SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION 133 
#define  SMP_FUNCTION_DISCOVER 132 
#define  SMP_FUNCTION_PHY_CONTROL 131 
#define  SMP_FUNCTION_REPORT_GENERAL 130 
#define  SMP_FUNCTION_REPORT_MANUFACTURER_INFORMATION 129 
#define  SMP_FUNCTION_REPORT_PHY_SATA 128 
 int /*<<< orphan*/  scif_cb_timer_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_continue_current_activity (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_config_route_info_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_discover_phy_control_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_initial_discover_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_report_general_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_report_phy_sata_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_spinup_hold_release_discover_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_target_reset_discover_response (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_smp_remote_device_decode_target_reset_phy_control_response (TYPE_4__*,int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_smp_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request,
   void                     * response_data,
   SCI_IO_STATUS              completion_status
)
{
   SMP_RESPONSE_T * smp_response = (SMP_RESPONSE_T *)response_data;
   SCI_STATUS       status       = SCI_FAILURE_UNSUPPORTED_INFORMATION_TYPE;

   if (fw_device->protocol_device.smp_device.smp_activity_timer != NULL)
   {
      //if there is a timer being used, recycle it now. Since we may
      //use the timer for other purpose next.
      scif_cb_timer_destroy(
         fw_device->domain->controller,
         fw_device->protocol_device.smp_device.smp_activity_timer
      );

      fw_device->protocol_device.smp_device.smp_activity_timer = NULL;
   }

   //if Core set the status of this io to be RETRY_REQUIRED, we should
   //retry the IO without even decode the response.
   if (completion_status == SCI_FAILURE_RETRY_REQUIRED)
   {
      scif_sas_smp_remote_device_continue_current_activity(
         fw_device, fw_request, SCI_FAILURE_RETRY_REQUIRED
      );

      return SCI_FAILURE_RETRY_REQUIRED;
   }

   //check the current smp request, decide what's next smp request to issue.
   switch (fw_device->protocol_device.smp_device.current_smp_request)
   {
      case SMP_FUNCTION_REPORT_GENERAL:
      {
         //interpret REPORT GENERAL response.
         status = scif_sas_smp_remote_device_decode_report_general_response(
            fw_device, smp_response
         );

         break;
      }

      case SMP_FUNCTION_REPORT_MANUFACTURER_INFORMATION:
      {
         // No need to perform any parsing.  Just want to see
         // the information in a trace if necessary.
         status = SCI_SUCCESS;
         break;
      }

      case SMP_FUNCTION_DISCOVER:
      {
         if (fw_device->protocol_device.smp_device.current_activity ==
                SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER)
         {
            //decode discover response
            status = scif_sas_smp_remote_device_decode_initial_discover_response(
                        fw_device, smp_response
                     );
         }
         else if (fw_device->protocol_device.smp_device.current_activity ==
                  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET)
         {
            //decode discover response as a polling result for a remote device
            //target reset.
            status =
               scif_sas_smp_remote_device_decode_target_reset_discover_response(
                  fw_device, smp_response
               );
         }
         else if (fw_device->protocol_device.smp_device.current_activity ==
                SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_SATA_SPINUP_HOLD_RELEASE)
         {
            //decode discover response
            status =
               scif_sas_smp_remote_device_decode_spinup_hold_release_discover_response(
                  fw_device, smp_response
               );
         }
         else
            ASSERT(0);
         break;
      }

      case SMP_FUNCTION_REPORT_PHY_SATA:
      {
         //decode the report phy sata response.
         status = scif_sas_smp_remote_device_decode_report_phy_sata_response(
            fw_device, smp_response
         );

         break;
      }

      case SMP_FUNCTION_PHY_CONTROL:
      {
         if (fw_device->protocol_device.smp_device.current_activity ==
                SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER)
         {
            //decode the phy control response.
            status = scif_sas_smp_remote_device_decode_discover_phy_control_response(
                        fw_device, smp_response
                     );
         }
         else if (fw_device->protocol_device.smp_device.current_activity ==
                     SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET)
         {
            //decode discover response as a polling result for a remote device
            //target reset.
            status = scif_sas_smp_remote_device_decode_target_reset_phy_control_response(
                        fw_device, smp_response
                     );
         }
         else if (fw_device->protocol_device.smp_device.current_activity ==
                     SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION)
         {
            //currently don't care about the status.
            status = SCI_SUCCESS;
         }
         else
            ASSERT(0);
         break;
      }

      case SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION:
      {
         //Note, currently we don't expect any abnormal status from config route info response,
         //but there is a possibility that we exceed the maximum route index. We will take care
         //of errors later.
         status = scif_sas_smp_remote_device_decode_config_route_info_response(
                     fw_device, smp_response
                  );
         break;
      }

      default:
         //unsupported case, TBD
         status = SCI_FAILURE_UNSUPPORTED_INFORMATION_TYPE;
         break;
   } //end of switch

   //Continue current activity based on response's decoding status.
   scif_sas_smp_remote_device_continue_current_activity(
      fw_device, fw_request, status
   );

   return status;
}