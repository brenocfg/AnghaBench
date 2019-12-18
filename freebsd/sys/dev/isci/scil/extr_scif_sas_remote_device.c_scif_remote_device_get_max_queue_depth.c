#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int U16 ;
struct TYPE_11__ {int capabilities; int ncq_depth; } ;
struct TYPE_12__ {TYPE_3__ sati_device; } ;
struct TYPE_13__ {TYPE_4__ stp_device; } ;
struct TYPE_15__ {TYPE_5__ protocol_device; int /*<<< orphan*/  core_object; } ;
struct TYPE_9__ {scalar_t__ attached_stp_target; } ;
struct TYPE_10__ {TYPE_1__ bits; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
typedef  TYPE_6__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE ; 
 int SCIF_REMOTE_DEVICE_NO_MAX_QUEUE_DEPTH ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_6__*) ; 

U16 scif_remote_device_get_max_queue_depth(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  protocols;

   scic_remote_device_get_protocols(fw_device->core_object, &protocols);

   // If the target is a SATA/STP target, then determine the queue depth
   // for either NCQ or for UDMA.
   if (protocols.u.bits.attached_stp_target)
   {
      if (fw_device->protocol_device.stp_device.sati_device.capabilities
          & SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE)
      {
         return fw_device->protocol_device.stp_device.sati_device.ncq_depth;
      }
      else
      {
         // At the moment, we only allow a single UDMA request to be queued.
         return 1;
      }
   }

   // For SSP devices return a no maximum queue depth supported.
   return SCIF_REMOTE_DEVICE_NO_MAX_QUEUE_DEPTH;
}