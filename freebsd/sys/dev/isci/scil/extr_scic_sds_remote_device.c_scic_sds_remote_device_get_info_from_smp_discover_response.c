#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  all; } ;
struct TYPE_14__ {TYPE_3__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_18__ {TYPE_4__ target_protocols; TYPE_1__ device_address; } ;
struct TYPE_15__ {int /*<<< orphan*/  all; } ;
struct TYPE_16__ {TYPE_5__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_17__ {TYPE_6__ protocols; TYPE_2__ attached_sas_address; } ;
typedef  TYPE_7__ SMP_RESPONSE_DISCOVER_T ;
typedef  TYPE_8__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */

void scic_sds_remote_device_get_info_from_smp_discover_response(
   SCIC_SDS_REMOTE_DEVICE_T    * this_device,
   SMP_RESPONSE_DISCOVER_T     * discover_response
)
{
   // decode discover_response to set sas_address to this_device.
   this_device->device_address.high =
      discover_response->attached_sas_address.high;

   this_device->device_address.low =
      discover_response->attached_sas_address.low;

   this_device->target_protocols.u.all = discover_response->protocols.u.all;
}