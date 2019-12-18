#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ current_activity; } ;
struct TYPE_6__ {TYPE_1__ smp_device; } ;
struct TYPE_7__ {TYPE_2__ protocol_device; } ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 

BOOL scif_sas_smp_remote_device_is_in_activity(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   return(fw_device->protocol_device.smp_device.current_activity
          != SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE);
}