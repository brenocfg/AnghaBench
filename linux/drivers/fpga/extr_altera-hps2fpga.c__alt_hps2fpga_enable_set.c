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
struct altera_hps2fpga_data {int remap_mask; int /*<<< orphan*/  l3reg; int /*<<< orphan*/  bridge_reset; } ;

/* Variables and functions */
 int ALT_L3_REMAP_MPUZERO_MSK ; 
 int /*<<< orphan*/  ALT_L3_REMAP_OFST ; 
 int /*<<< orphan*/  l3_remap_lock ; 
 int l3_remap_shadow ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int _alt_hps2fpga_enable_set(struct altera_hps2fpga_data *priv,
				    bool enable)
{
	unsigned long flags;
	int ret;

	/* bring bridge out of reset */
	if (enable)
		ret = reset_control_deassert(priv->bridge_reset);
	else
		ret = reset_control_assert(priv->bridge_reset);
	if (ret)
		return ret;

	/* Allow bridge to be visible to L3 masters or not */
	if (priv->remap_mask) {
		spin_lock_irqsave(&l3_remap_lock, flags);
		l3_remap_shadow |= ALT_L3_REMAP_MPUZERO_MSK;

		if (enable)
			l3_remap_shadow |= priv->remap_mask;
		else
			l3_remap_shadow &= ~priv->remap_mask;

		ret = regmap_write(priv->l3reg, ALT_L3_REMAP_OFST,
				   l3_remap_shadow);
		spin_unlock_irqrestore(&l3_remap_lock, flags);
	}

	return ret;
}