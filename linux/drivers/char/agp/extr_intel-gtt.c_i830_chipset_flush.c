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
struct TYPE_2__ {scalar_t__ registers; } ;

/* Variables and functions */
 scalar_t__ I830_HIC ; 
 TYPE_1__ intel_private ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wbinvd_on_all_cpus () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void i830_chipset_flush(void)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);

	/* Forcibly evict everything from the CPU write buffers.
	 * clflush appears to be insufficient.
	 */
	wbinvd_on_all_cpus();

	/* Now we've only seen documents for this magic bit on 855GM,
	 * we hope it exists for the other gen2 chipsets...
	 *
	 * Also works as advertised on my 845G.
	 */
	writel(readl(intel_private.registers+I830_HIC) | (1<<31),
	       intel_private.registers+I830_HIC);

	while (readl(intel_private.registers+I830_HIC) & (1<<31)) {
		if (time_after(jiffies, timeout))
			break;

		udelay(50);
	}
}