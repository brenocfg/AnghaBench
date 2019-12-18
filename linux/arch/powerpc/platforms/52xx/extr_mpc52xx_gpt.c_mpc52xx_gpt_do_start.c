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
typedef  int u64 ;
typedef  int u32 ;
struct mpc52xx_gpt_priv {int wdt_mode; int /*<<< orphan*/  lock; TYPE_1__* regs; scalar_t__ ipb_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MPC52xx_GPT_IS_WDT ; 
 int MPC52xx_GPT_MODE_CONTINUOUS ; 
 int MPC52xx_GPT_MODE_COUNTER_ENABLE ; 
 int MPC52xx_GPT_MODE_IRQ_EN ; 
 int MPC52xx_GPT_MODE_MS_GPIO ; 
 int MPC52xx_GPT_MODE_MS_MASK ; 
 int MPC52xx_GPT_MODE_WDT_EN ; 
 int /*<<< orphan*/  clrsetbits_be32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpc52xx_gpt_do_start(struct mpc52xx_gpt_priv *gpt, u64 period,
				int continuous, int as_wdt)
{
	u32 clear, set;
	u64 clocks;
	u32 prescale;
	unsigned long flags;

	clear = MPC52xx_GPT_MODE_MS_MASK | MPC52xx_GPT_MODE_CONTINUOUS;
	set = MPC52xx_GPT_MODE_MS_GPIO | MPC52xx_GPT_MODE_COUNTER_ENABLE;
	if (as_wdt) {
		clear |= MPC52xx_GPT_MODE_IRQ_EN;
		set |= MPC52xx_GPT_MODE_WDT_EN;
	} else if (continuous)
		set |= MPC52xx_GPT_MODE_CONTINUOUS;

	/* Determine the number of clocks in the requested period.  64 bit
	 * arithmatic is done here to preserve the precision until the value
	 * is scaled back down into the u32 range.  Period is in 'ns', bus
	 * frequency is in Hz. */
	clocks = period * (u64)gpt->ipb_freq;
	do_div(clocks, 1000000000); /* Scale it down to ns range */

	/* This device cannot handle a clock count greater than 32 bits */
	if (clocks > 0xffffffff)
		return -EINVAL;

	/* Calculate the prescaler and count values from the clocks value.
	 * 'clocks' is the number of clock ticks in the period.  The timer
	 * has 16 bit precision and a 16 bit prescaler.  Prescaler is
	 * calculated by integer dividing the clocks by 0x10000 (shifting
	 * down 16 bits) to obtain the smallest possible divisor for clocks
	 * to get a 16 bit count value.
	 *
	 * Note: the prescale register is '1' based, not '0' based.  ie. a
	 * value of '1' means divide the clock by one.  0xffff divides the
	 * clock by 0xffff.  '0x0000' does not divide by zero, but wraps
	 * around and divides by 0x10000.  That is why prescale must be
	 * a u32 variable, not a u16, for this calculation. */
	prescale = (clocks >> 16) + 1;
	do_div(clocks, prescale);
	if (clocks > 0xffff) {
		pr_err("calculation error; prescale:%x clocks:%llx\n",
		       prescale, clocks);
		return -EINVAL;
	}

	/* Set and enable the timer, reject an attempt to use a wdt as gpt */
	raw_spin_lock_irqsave(&gpt->lock, flags);
	if (as_wdt)
		gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
	else if ((gpt->wdt_mode & MPC52xx_GPT_IS_WDT) != 0) {
		raw_spin_unlock_irqrestore(&gpt->lock, flags);
		return -EBUSY;
	}
	out_be32(&gpt->regs->count, prescale << 16 | clocks);
	clrsetbits_be32(&gpt->regs->mode, clear, set);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	return 0;
}