#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  chip_id; } ;
struct TYPE_5__ {int xstop_reason; TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ xstop_error; } ;
struct OpalHMIEvent {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  reason ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void print_npu_checkstop_reason(const char *level,
					struct OpalHMIEvent *hmi_evt)
{
	uint8_t reason, reason_count, i;

	/*
	 * We may not have a checkstop reason on some combination of
	 * hardware and/or skiboot version
	 */
	if (!hmi_evt->u.xstop_error.xstop_reason) {
		printk("%s	NPU checkstop on chip %x\n", level,
			be32_to_cpu(hmi_evt->u.xstop_error.u.chip_id));
		return;
	}

	/*
	 * NPU2 has 3 FIRs. Reason encoded on a byte as:
	 *   2 bits for the FIR number
	 *   6 bits for the bit number
	 * It may be possible to find several reasons.
	 *
	 * We don't display a specific message per FIR bit as there
	 * are too many and most are meaningless without the workbook
	 * and/or hw team help anyway.
	 */
	reason_count = sizeof(hmi_evt->u.xstop_error.xstop_reason) /
		sizeof(reason);
	for (i = 0; i < reason_count; i++) {
		reason = (hmi_evt->u.xstop_error.xstop_reason >> (8 * i)) & 0xFF;
		if (reason)
			printk("%s	NPU checkstop on chip %x: FIR%d bit %d is set\n",
				level,
				be32_to_cpu(hmi_evt->u.xstop_error.u.chip_id),
				reason >> 6, reason & 0x3F);
	}
}