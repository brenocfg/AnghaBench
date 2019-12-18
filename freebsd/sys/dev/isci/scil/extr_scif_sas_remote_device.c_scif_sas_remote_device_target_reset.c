#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ current_activity; } ;
struct TYPE_9__ {TYPE_1__ smp_device; } ;
struct TYPE_11__ {TYPE_2__ protocol_device; } ;
struct TYPE_10__ {int /*<<< orphan*/  core_object; TYPE_4__* containing_device; int /*<<< orphan*/ * ea_target_reset_request_scheduled; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_port_hard_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_get_suggested_reset_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_domain_get_scic_port_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_start_target_reset (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

void scif_sas_remote_device_target_reset(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request
)
{
   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "scif_sas_remote_device_target_reset! fw_device:0x%x fw_request:0x%x\n",
      fw_device, fw_request
   ));

   if (fw_device->containing_device == NULL)
   {
      SCI_PORT_HANDLE_T port;

      port = scif_domain_get_scic_port_handle(fw_device->domain);

      //Direct attached device target reset.
      //calling core to do port reset. The fw_request will not be used here.
      scic_port_hard_reset(
         port,
         scic_remote_device_get_suggested_reset_timeout(fw_device->core_object)
      );
   }
   else
   {  //Expander attached device target reset.

      if ( fw_device->containing_device->protocol_device.smp_device.current_activity
              == SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET )
      {
         //The containing expander is in the middle of target resetting other of its
         //remote disks. Flag this remote device to be target reset later.
         SCIF_LOG_INFO((
            sci_base_object_get_logger(fw_device),
            SCIF_LOG_OBJECT_REMOTE_DEVICE,
            "scif_sas_remote_device_target_reset DELAYED! fw_device:0x%x fw_request:0x%x\n",
            fw_device, fw_request
         ));

         fw_device->ea_target_reset_request_scheduled = fw_request;
         return;
      }

      //set current_activity and current_smp_request to expander device.
      scif_sas_smp_remote_device_start_target_reset(
         fw_device->containing_device, fw_device, fw_request);
   }

   scic_remote_device_reset(fw_device->core_object);
}