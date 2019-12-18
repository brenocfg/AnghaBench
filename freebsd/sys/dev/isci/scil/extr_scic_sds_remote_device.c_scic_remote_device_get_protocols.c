#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  all; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_12__ {TYPE_3__ target_protocols; } ;
struct TYPE_8__ {int /*<<< orphan*/  all; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_4__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_5__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 

void scic_remote_device_get_protocols(
   SCI_REMOTE_DEVICE_HANDLE_T          remote_device,
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T * protocols
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)
                                            remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_get_protocols(0x%x) enter\n",
      remote_device
   ));

   protocols->u.all = this_device->target_protocols.u.all;
}