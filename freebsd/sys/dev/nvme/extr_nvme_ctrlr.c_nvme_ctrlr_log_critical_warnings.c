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
typedef  int uint8_t ;
struct nvme_controller {int dummy; } ;

/* Variables and functions */
 int NVME_CRIT_WARN_ST_AVAILABLE_SPARE ; 
 int NVME_CRIT_WARN_ST_DEVICE_RELIABILITY ; 
 int NVME_CRIT_WARN_ST_READ_ONLY ; 
 int NVME_CRIT_WARN_ST_RESERVED_MASK ; 
 int NVME_CRIT_WARN_ST_TEMPERATURE ; 
 int NVME_CRIT_WARN_ST_VOLATILE_MEMORY_BACKUP ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*,...) ; 

__attribute__((used)) static void
nvme_ctrlr_log_critical_warnings(struct nvme_controller *ctrlr,
    uint8_t state)
{

	if (state & NVME_CRIT_WARN_ST_AVAILABLE_SPARE)
		nvme_printf(ctrlr, "available spare space below threshold\n");

	if (state & NVME_CRIT_WARN_ST_TEMPERATURE)
		nvme_printf(ctrlr, "temperature above threshold\n");

	if (state & NVME_CRIT_WARN_ST_DEVICE_RELIABILITY)
		nvme_printf(ctrlr, "device reliability degraded\n");

	if (state & NVME_CRIT_WARN_ST_READ_ONLY)
		nvme_printf(ctrlr, "media placed in read only mode\n");

	if (state & NVME_CRIT_WARN_ST_VOLATILE_MEMORY_BACKUP)
		nvme_printf(ctrlr, "volatile memory backup device failed\n");

	if (state & NVME_CRIT_WARN_ST_RESERVED_MASK)
		nvme_printf(ctrlr,
		    "unknown critical warning(s): state = 0x%02x\n", state);
}