#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ current_state_id; } ;
struct TYPE_16__ {TYPE_1__ state_machine; } ;
struct TYPE_25__ {TYPE_10__ parent; TYPE_6__* state_handlers; int /*<<< orphan*/  device_start_in_progress_count; } ;
struct TYPE_20__ {int /*<<< orphan*/  scheduled_activity; } ;
struct TYPE_21__ {TYPE_4__ smp_device; } ;
struct TYPE_24__ {int /*<<< orphan*/  parent; TYPE_5__ protocol_device; int /*<<< orphan*/ * containing_device; int /*<<< orphan*/  core_object; } ;
struct TYPE_18__ {scalar_t__ attached_smp_target; } ;
struct TYPE_19__ {TYPE_2__ bits; } ;
struct TYPE_23__ {TYPE_3__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* device_start_complete_handler ) (TYPE_10__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_7__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  TYPE_8__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_9__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_9__*) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_start_discover (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ *) ; 

void scif_sas_domain_remote_device_start_complete(
   SCIF_SAS_DOMAIN_T        * fw_domain,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_remote_device_start_complete(0x%x, 0x%x) enter\n",
      fw_domain, fw_device
   ));

   // If a device is being started/start completed, then we must be
   // during discovery.
   ASSERT(fw_domain->parent.state_machine.current_state_id
          == SCI_BASE_DOMAIN_STATE_DISCOVERING);

   scic_remote_device_get_protocols(fw_device->core_object, &dev_protocols);

   // Decrement the number of devices being started and check to see
   // if all have finished being started or failed as the case may be.
   fw_domain->device_start_in_progress_count--;

   if ( dev_protocols.u.bits.attached_smp_target )
   {
      if ( fw_device->containing_device == NULL )
         //kick off the smp discover process if this expander is direct attached.
         scif_sas_smp_remote_device_start_discover(fw_device);
      else
         //mark this device, the discover process of this device will start after
         //its containing smp device finish discover.
         fw_device->protocol_device.smp_device.scheduled_activity =
            SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER;
   }
   else
   {
      fw_domain->state_handlers->device_start_complete_handler(
         &fw_domain->parent, &fw_device->parent
      );
   }
}