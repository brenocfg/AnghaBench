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
typedef  int u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct sprd_pll {size_t regs_num; int fflag; int k1; int k2; } ;

/* Variables and functions */
 int CLK_PLL_10M ; 
 int CLK_PLL_1M ; 
 int DIV_ROUND_CLOSEST_ULL (int,size_t) ; 
 unsigned long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLL_DIV_S ; 
 int /*<<< orphan*/  PLL_KINT ; 
 int /*<<< orphan*/  PLL_N ; 
 int /*<<< orphan*/  PLL_NINT ; 
 int /*<<< orphan*/  PLL_POSTDIV ; 
 int /*<<< orphan*/  PLL_PREDIV ; 
 int /*<<< orphan*/  PLL_SDM_EN ; 
 size_t __ffs (size_t) ; 
 size_t* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 scalar_t__ pinternal (struct sprd_pll const*,size_t*,int /*<<< orphan*/ ) ; 
 int pinternal_val (struct sprd_pll const*,size_t*,int /*<<< orphan*/ ) ; 
 int pll_get_refin (struct sprd_pll const*) ; 
 size_t pmask (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pwidth (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 size_t sprd_pll_read (struct sprd_pll const*,size_t) ; 

__attribute__((used)) static unsigned long _sprd_pll_recalc_rate(const struct sprd_pll *pll,
					   unsigned long parent_rate)
{
	u32 *cfg;
	u32 i, mask, regs_num = pll->regs_num;
	unsigned long rate, nint, kint = 0;
	u64 refin;
	u16 k1, k2;

	cfg = kcalloc(regs_num, sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	for (i = 0; i < regs_num; i++)
		cfg[i] = sprd_pll_read(pll, i);

	refin = pll_get_refin(pll);

	if (pinternal(pll, cfg, PLL_PREDIV))
		refin = refin * 2;

	if (pwidth(pll, PLL_POSTDIV) &&
	    ((pll->fflag == 1 && pinternal(pll, cfg, PLL_POSTDIV)) ||
	     (!pll->fflag && !pinternal(pll, cfg, PLL_POSTDIV))))
		refin = refin / 2;

	if (!pinternal(pll, cfg, PLL_DIV_S)) {
		rate = refin * pinternal_val(pll, cfg, PLL_N) * CLK_PLL_10M;
	} else {
		nint = pinternal_val(pll, cfg, PLL_NINT);
		if (pinternal(pll, cfg, PLL_SDM_EN))
			kint = pinternal_val(pll, cfg, PLL_KINT);

		mask = pmask(pll, PLL_KINT);

		k1 = pll->k1;
		k2 = pll->k2;
		rate = DIV_ROUND_CLOSEST_ULL(refin * kint * k1,
					 ((mask >> __ffs(mask)) + 1)) *
					 k2 + refin * nint * CLK_PLL_1M;
	}

	kfree(cfg);
	return rate;
}