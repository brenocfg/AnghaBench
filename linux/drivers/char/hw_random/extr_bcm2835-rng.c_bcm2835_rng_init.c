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
struct hwrng {int dummy; } ;
struct bcm2835_rng_priv {scalar_t__ mask_interrupts; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RNG_CTRL ; 
 int /*<<< orphan*/  RNG_INT_MASK ; 
 int /*<<< orphan*/  RNG_INT_OFF ; 
 int /*<<< orphan*/  RNG_RBGEN ; 
 int /*<<< orphan*/  RNG_STATUS ; 
 int /*<<< orphan*/  RNG_WARMUP_COUNT ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_readl (struct bcm2835_rng_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_writel (struct bcm2835_rng_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_rng_priv* to_rng_priv (struct hwrng*) ; 

__attribute__((used)) static int bcm2835_rng_init(struct hwrng *rng)
{
	struct bcm2835_rng_priv *priv = to_rng_priv(rng);
	int ret = 0;
	u32 val;

	if (!IS_ERR(priv->clk)) {
		ret = clk_prepare_enable(priv->clk);
		if (ret)
			return ret;
	}

	if (priv->mask_interrupts) {
		/* mask the interrupt */
		val = rng_readl(priv, RNG_INT_MASK);
		val |= RNG_INT_OFF;
		rng_writel(priv, val, RNG_INT_MASK);
	}

	/* set warm-up count & enable */
	rng_writel(priv, RNG_WARMUP_COUNT, RNG_STATUS);
	rng_writel(priv, RNG_RBGEN, RNG_CTRL);

	return ret;
}