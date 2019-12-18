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
struct sprd_pll {size_t regs_num; int fflag; int fvco; int /*<<< orphan*/  udelay; int /*<<< orphan*/  itable; } ;
struct reg_cfg {size_t msk; size_t val; } ;

/* Variables and functions */
 int CLK_PLL_1M ; 
 unsigned long DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLL_DIV_S ; 
 int /*<<< orphan*/  PLL_IBIAS ; 
 int /*<<< orphan*/  PLL_KINT ; 
 int /*<<< orphan*/  PLL_NINT ; 
 int /*<<< orphan*/  PLL_POSTDIV ; 
 int /*<<< orphan*/  PLL_PREDIV ; 
 int /*<<< orphan*/  PLL_SDM_EN ; 
 int SPRD_PLL_WRITE_CHECK (struct sprd_pll const*,size_t,int,size_t) ; 
 size_t do_div (int,int) ; 
 struct reg_cfg* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct reg_cfg*) ; 
 size_t pindex (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 size_t pll_get_ibias (int,int /*<<< orphan*/ ) ; 
 int pll_get_refin (struct sprd_pll const*) ; 
 size_t pmask (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 size_t pshift (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 size_t pwidth (struct sprd_pll const*,int /*<<< orphan*/ ) ; 
 size_t sprd_pll_read (struct sprd_pll const*,size_t) ; 
 int /*<<< orphan*/  sprd_pll_write (struct sprd_pll const*,size_t,int,size_t) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _sprd_pll_set_rate(const struct sprd_pll *pll,
			      unsigned long rate,
			      unsigned long parent_rate)
{
	struct reg_cfg *cfg;
	int ret = 0;
	u32 mask, shift, width, ibias_val, index;
	u32 regs_num = pll->regs_num, i = 0;
	unsigned long kint, nint;
	u64 tmp, refin, fvco = rate;

	cfg = kcalloc(regs_num, sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	refin = pll_get_refin(pll);

	mask = pmask(pll, PLL_PREDIV);
	index = pindex(pll, PLL_PREDIV);
	width = pwidth(pll, PLL_PREDIV);
	if (width && (sprd_pll_read(pll, index) & mask))
		refin = refin * 2;

	mask = pmask(pll, PLL_POSTDIV);
	index = pindex(pll, PLL_POSTDIV);
	width = pwidth(pll, PLL_POSTDIV);
	cfg[index].msk = mask;
	if (width && ((pll->fflag == 1 && fvco <= pll->fvco) ||
		      (pll->fflag == 0 && fvco > pll->fvco)))
		cfg[index].val |= mask;

	if (width && fvco <= pll->fvco)
		fvco = fvco * 2;

	mask = pmask(pll, PLL_DIV_S);
	index = pindex(pll, PLL_DIV_S);
	cfg[index].val |= mask;
	cfg[index].msk |= mask;

	mask = pmask(pll, PLL_SDM_EN);
	index = pindex(pll, PLL_SDM_EN);
	cfg[index].val |= mask;
	cfg[index].msk |= mask;

	nint = do_div(fvco, refin * CLK_PLL_1M);
	mask = pmask(pll, PLL_NINT);
	index = pindex(pll, PLL_NINT);
	shift = pshift(pll, PLL_NINT);
	cfg[index].val |= (nint << shift) & mask;
	cfg[index].msk |= mask;

	mask = pmask(pll, PLL_KINT);
	index = pindex(pll, PLL_KINT);
	width = pwidth(pll, PLL_KINT);
	shift = pshift(pll, PLL_KINT);
	tmp = fvco - refin * nint * CLK_PLL_1M;
	tmp = do_div(tmp, 10000) * ((mask >> shift) + 1);
	kint = DIV_ROUND_CLOSEST_ULL(tmp, refin * 100);
	cfg[index].val |= (kint << shift) & mask;
	cfg[index].msk |= mask;

	ibias_val = pll_get_ibias(fvco, pll->itable);

	mask = pmask(pll, PLL_IBIAS);
	index = pindex(pll, PLL_IBIAS);
	shift = pshift(pll, PLL_IBIAS);
	cfg[index].val |= ibias_val << shift & mask;
	cfg[index].msk |= mask;

	for (i = 0; i < regs_num; i++) {
		if (cfg[i].msk) {
			sprd_pll_write(pll, i, cfg[i].msk, cfg[i].val);
			ret |= SPRD_PLL_WRITE_CHECK(pll, i, cfg[i].msk,
						   cfg[i].val);
		}
	}

	if (!ret)
		udelay(pll->udelay);

	kfree(cfg);
	return ret;
}