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
struct mstp_clock {int index; struct cpg_mssr_priv* priv; } ;
struct device {int dummy; } ;
struct cpg_mssr_priv {scalar_t__ base; scalar_t__ stbyctrl; int /*<<< orphan*/  rmw_lock; struct device* dev; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ETIMEDOUT ; 
 scalar_t__ MSTPSR (unsigned int) ; 
 scalar_t__ SMSTPCR (unsigned int) ; 
 scalar_t__ STBCR (unsigned int) ; 
 int /*<<< orphan*/  barrier_data (scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,unsigned int) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mstp_clock* to_mstp_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cpg_mstp_clock_endisable(struct clk_hw *hw, bool enable)
{
	struct mstp_clock *clock = to_mstp_clock(hw);
	struct cpg_mssr_priv *priv = clock->priv;
	unsigned int reg = clock->index / 32;
	unsigned int bit = clock->index % 32;
	struct device *dev = priv->dev;
	u32 bitmask = BIT(bit);
	unsigned long flags;
	unsigned int i;
	u32 value;

	dev_dbg(dev, "MSTP %u%02u/%pC %s\n", reg, bit, hw->clk,
		enable ? "ON" : "OFF");
	spin_lock_irqsave(&priv->rmw_lock, flags);

	if (priv->stbyctrl) {
		value = readb(priv->base + STBCR(reg));
		if (enable)
			value &= ~bitmask;
		else
			value |= bitmask;
		writeb(value, priv->base + STBCR(reg));

		/* dummy read to ensure write has completed */
		readb(priv->base + STBCR(reg));
		barrier_data(priv->base + STBCR(reg));
	} else {
		value = readl(priv->base + SMSTPCR(reg));
		if (enable)
			value &= ~bitmask;
		else
			value |= bitmask;
		writel(value, priv->base + SMSTPCR(reg));
	}

	spin_unlock_irqrestore(&priv->rmw_lock, flags);

	if (!enable || priv->stbyctrl)
		return 0;

	for (i = 1000; i > 0; --i) {
		if (!(readl(priv->base + MSTPSR(reg)) & bitmask))
			break;
		cpu_relax();
	}

	if (!i) {
		dev_err(dev, "Failed to enable SMSTP %p[%d]\n",
			priv->base + SMSTPCR(reg), bit);
		return -ETIMEDOUT;
	}

	return 0;
}