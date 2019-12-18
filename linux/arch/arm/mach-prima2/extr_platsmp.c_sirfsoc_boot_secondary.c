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
struct task_struct {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int HZ ; 
 scalar_t__ SIRFSOC_CPU1_JUMPADDR_OFFSET ; 
 scalar_t__ SIRFSOC_CPU1_WAKEMAGIC_OFFSET ; 
 int __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  boot_lock ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  clk_ids ; 
 int cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  dsb_sev () ; 
 int jiffies ; 
 int /*<<< orphan*/  mb () ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int prima2_pen_release ; 
 int /*<<< orphan*/  sirfsoc_secondary_startup ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_cache_w (int*) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sirfsoc_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
	struct device_node *np;

	np = of_find_matching_node(NULL, clk_ids);
	if (!np)
		return -ENODEV;

	clk_base = of_iomap(np, 0);
	if (!clk_base)
		return -ENOMEM;

	/*
	 * write the address of secondary startup into the clkc register
	 * at offset 0x2bC, then write the magic number 0x3CAF5D62 to the
	 * clkc register at offset 0x2b8, which is what boot rom code is
	 * waiting for. This would wake up the secondary core from WFE
	 */
#define SIRFSOC_CPU1_JUMPADDR_OFFSET 0x2bc
	__raw_writel(__pa_symbol(sirfsoc_secondary_startup),
		clk_base + SIRFSOC_CPU1_JUMPADDR_OFFSET);

#define SIRFSOC_CPU1_WAKEMAGIC_OFFSET 0x2b8
	__raw_writel(0x3CAF5D62,
		clk_base + SIRFSOC_CPU1_WAKEMAGIC_OFFSET);

	/* make sure write buffer is drained */
	mb();

	spin_lock(&boot_lock);

	/*
	 * The secondary processor is waiting to be released from
	 * the holding pen - release it, then wait for it to flag
	 * that it has been released by resetting prima2_pen_release.
	 *
	 * Note that "prima2_pen_release" is the hardware CPU ID, whereas
	 * "cpu" is Linux's internal ID.
	 */
	prima2_pen_release = cpu_logical_map(cpu);
	sync_cache_w(&prima2_pen_release);

	/*
	 * Send the secondary CPU SEV, thereby causing the boot monitor to read
	 * the JUMPADDR and WAKEMAGIC, and branch to the address found there.
	 */
	dsb_sev();

	timeout = jiffies + (1 * HZ);
	while (time_before(jiffies, timeout)) {
		smp_rmb();
		if (prima2_pen_release == -1)
			break;

		udelay(10);
	}

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then wait for it to finish
	 */
	spin_unlock(&boot_lock);

	return prima2_pen_release != -1 ? -ENOSYS : 0;
}