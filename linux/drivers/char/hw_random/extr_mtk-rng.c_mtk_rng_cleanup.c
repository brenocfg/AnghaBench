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
struct mtk_rng {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 scalar_t__ RNG_CTRL ; 
 int /*<<< orphan*/  RNG_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct mtk_rng* to_mtk_rng (struct hwrng*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_rng_cleanup(struct hwrng *rng)
{
	struct mtk_rng *priv = to_mtk_rng(rng);
	u32 val;

	val = readl(priv->base + RNG_CTRL);
	val &= ~RNG_EN;
	writel(val, priv->base + RNG_CTRL);

	clk_disable_unprepare(priv->clk);
}