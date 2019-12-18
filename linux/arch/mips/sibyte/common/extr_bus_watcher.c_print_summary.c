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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ G_SCD_BERR_DCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ G_SCD_BERR_RID (int /*<<< orphan*/ ) ; 
 int G_SCD_BERR_TID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void print_summary(uint32_t status, uint32_t l2_err,
			  uint32_t memio_err)
{
	printk("Bus watcher error counters: %08x %08x\n", l2_err, memio_err);
	printk("\nLast recorded signature:\n");
	printk("Request %02x from %d, answered by %d with Dcode %d\n",
	       (unsigned int)(G_SCD_BERR_TID(status) & 0x3f),
	       (int)(G_SCD_BERR_TID(status) >> 6),
	       (int)G_SCD_BERR_RID(status),
	       (int)G_SCD_BERR_DCODE(status));
}