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
struct timer_cker {int /*<<< orphan*/  lock; int /*<<< orphan*/  timpre; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long __bestmult (struct clk_hw*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct timer_cker* to_timer_cker (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_ker_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct timer_cker *tim_ker = to_timer_cker(hw);
	unsigned long flags = 0;
	unsigned long factor = __bestmult(hw, rate, parent_rate);
	int ret = 0;

	spin_lock_irqsave(tim_ker->lock, flags);

	switch (factor) {
	case 1:
		break;
	case 2:
		writel_relaxed(0, tim_ker->timpre);
		break;
	case 4:
		writel_relaxed(1, tim_ker->timpre);
		break;
	default:
		ret = -EINVAL;
	}
	spin_unlock_irqrestore(tim_ker->lock, flags);

	return ret;
}