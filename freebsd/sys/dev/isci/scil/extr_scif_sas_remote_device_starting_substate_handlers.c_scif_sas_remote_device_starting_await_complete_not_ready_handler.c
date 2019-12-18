#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */

__attribute__((used)) static
void scif_sas_remote_device_starting_await_complete_not_ready_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U32                        reason_code
)
{
}