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
typedef  int /*<<< orphan*/  u32 ;
struct rdt_resource {int num_closid; int /*<<< orphan*/  default_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBA_MAX_MBPS ; 

void setup_default_ctrlval(struct rdt_resource *r, u32 *dc, u32 *dm)
{
	int i;

	/*
	 * Initialize the Control MSRs to having no control.
	 * For Cache Allocation: Set all bits in cbm
	 * For Memory Allocation: Set b/w requested to 100%
	 * and the bandwidth in MBps to U32_MAX
	 */
	for (i = 0; i < r->num_closid; i++, dc++, dm++) {
		*dc = r->default_ctrl;
		*dm = MBA_MAX_MBPS;
	}
}