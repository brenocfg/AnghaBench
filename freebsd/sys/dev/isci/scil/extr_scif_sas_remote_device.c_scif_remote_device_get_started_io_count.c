#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_2__ {scalar_t__ task_request_count; scalar_t__ request_count; } ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */

U32 scif_remote_device_get_started_io_count(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCIF_SAS_REMOTE_DEVICE_T * this_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                                            remote_device;

   return this_device->request_count - this_device->task_request_count;
}