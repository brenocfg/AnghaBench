#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_14__ {TYPE_3__ parent; int /*<<< orphan*/  core_object; } ;
struct TYPE_10__ {scalar_t__ attached_smp_target; } ;
struct TYPE_11__ {TYPE_1__ bits; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  TYPE_4__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE_CONFIG ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_FINAL ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_remote_device_destruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_remote_device_deinitialize_state_logging (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_removed (TYPE_5__*) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_stopped_destruct_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device
)
{
   SCI_STATUS                 status;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                                          remote_device;

   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;
   scic_remote_device_get_protocols(fw_device->core_object, &dev_protocols);

   //For smp device, need to clear its smp phy list first.
   if(dev_protocols.u.bits.attached_smp_target)
      scif_sas_smp_remote_device_removed(fw_device);

   status = scic_remote_device_destruct(fw_device->core_object);
   if (status == SCI_SUCCESS)
   {
      sci_base_state_machine_change_state(
         &fw_device->parent.state_machine, SCI_BASE_REMOTE_DEVICE_STATE_FINAL
      );

      scif_sas_remote_device_deinitialize_state_logging(fw_device);
   }
   else
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_REMOTE_DEVICE_CONFIG,
         "Device:0x%x Status:0x%x failed to destruct core device\n",
         fw_device
      ));
   }

   return status;
}