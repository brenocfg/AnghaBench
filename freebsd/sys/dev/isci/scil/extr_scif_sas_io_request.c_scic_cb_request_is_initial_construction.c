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
struct TYPE_15__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_11__ {scalar_t__ state; } ;
struct TYPE_12__ {TYPE_3__ sequence; } ;
struct TYPE_14__ {TYPE_4__ stp; TYPE_7__* device; } ;
struct TYPE_9__ {scalar_t__ attached_stp_target; } ;
struct TYPE_10__ {TYPE_1__ bits; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  TYPE_5__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  TYPE_6__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_5__*) ; 

BOOL scic_cb_request_is_initial_construction(
   void * scic_user_io_request
)
{
   SCIF_SAS_REQUEST_T * fw_request = (SCIF_SAS_REQUEST_T*)
                                   scic_user_io_request;
   SCIF_SAS_REMOTE_DEVICE_T* fw_device = fw_request->device;

   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;
   scic_remote_device_get_protocols(fw_device->core_object, &dev_protocols);

   if (dev_protocols.u.bits.attached_stp_target
       && fw_request->stp.sequence.state == SATI_SEQUENCE_STATE_INCOMPLETE)
      return FALSE;

   return TRUE;
}