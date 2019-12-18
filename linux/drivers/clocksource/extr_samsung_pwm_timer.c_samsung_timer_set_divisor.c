#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int div_base; } ;
struct TYPE_4__ {scalar_t__ base; TYPE_1__ variant; } ;

/* Variables and functions */
 scalar_t__ REG_TCFG1 ; 
 int TCFG1_MUX_MASK ; 
 int TCFG1_SHIFT (unsigned int) ; 
 int fls (int) ; 
 TYPE_2__ pwm ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  samsung_pwm_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void samsung_timer_set_divisor(unsigned int channel, u8 divisor)
{
	u8 shift = TCFG1_SHIFT(channel);
	unsigned long flags;
	u32 reg;
	u8 bits;

	bits = (fls(divisor) - 1) - pwm.variant.div_base;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	reg = readl(pwm.base + REG_TCFG1);
	reg &= ~(TCFG1_MUX_MASK << shift);
	reg |= bits << shift;
	writel(reg, pwm.base + REG_TCFG1);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
}