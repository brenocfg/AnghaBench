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
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ETIME ; 
 scalar_t__ SRC_SCR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  scr_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ src_base ; 
 int* sw_reset_bits ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int imx_src_reset_module(struct reset_controller_dev *rcdev,
		unsigned long sw_reset_idx)
{
	unsigned long timeout;
	unsigned long flags;
	int bit;
	u32 val;

	if (!src_base)
		return -ENODEV;

	if (sw_reset_idx >= ARRAY_SIZE(sw_reset_bits))
		return -EINVAL;

	bit = 1 << sw_reset_bits[sw_reset_idx];

	spin_lock_irqsave(&scr_lock, flags);
	val = readl_relaxed(src_base + SRC_SCR);
	val |= bit;
	writel_relaxed(val, src_base + SRC_SCR);
	spin_unlock_irqrestore(&scr_lock, flags);

	timeout = jiffies + msecs_to_jiffies(1000);
	while (readl(src_base + SRC_SCR) & bit) {
		if (time_after(jiffies, timeout))
			return -ETIME;
		cpu_relax();
	}

	return 0;
}