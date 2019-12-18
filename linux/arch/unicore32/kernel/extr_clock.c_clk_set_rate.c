#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct clk {unsigned long rate; } ;
struct TYPE_6__ {int rate; } ;
struct TYPE_5__ {unsigned long rate; unsigned long cfg; unsigned long div; unsigned long mrate; int prate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PM_DIVCFG ; 
 int PM_DIVCFG_VGACLK (unsigned long) ; 
 int PM_DIVCFG_VGACLK_MASK ; 
 int /*<<< orphan*/  PM_DIVSTATUS ; 
 int /*<<< orphan*/  PM_PCGR ; 
 int PM_PCGR_VGACLK ; 
 int /*<<< orphan*/  PM_PLLDFCDONE ; 
 int PM_PLLDFCDONE_SYSDFC ; 
 int PM_PLLDFCDONE_VGADFC ; 
 int /*<<< orphan*/  PM_PLLSYSCFG ; 
 int /*<<< orphan*/  PM_PLLVGACFG ; 
 int /*<<< orphan*/  PM_PMCR ; 
 int PM_PMCR_CFBSYS ; 
 int PM_PMCR_CFBVGA ; 
 int /*<<< orphan*/  PM_SWRESET ; 
 int PM_SWRESET_VGADIV ; 
 TYPE_3__ clk_bclk32_clk ; 
 struct clk clk_mclk_clk ; 
 struct clk clk_vga_clk ; 
 TYPE_1__* mclk_clk_table ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 TYPE_1__* vga_clk_table ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	if (clk == &clk_vga_clk) {
		unsigned long pll_vgacfg, pll_vgadiv;
		int ret, i;

		/* lookup vga_clk_table */
		ret = -EINVAL;
		for (i = 0; i < ARRAY_SIZE(vga_clk_table); i++) {
			if (rate == vga_clk_table[i].rate) {
				pll_vgacfg = vga_clk_table[i].cfg;
				pll_vgadiv = vga_clk_table[i].div;
				ret = 0;
				break;
			}
		}

		if (ret)
			return ret;

		if (readl(PM_PLLVGACFG) == pll_vgacfg)
			return 0;

		/* set pll vga cfg reg. */
		writel(pll_vgacfg, PM_PLLVGACFG);

		writel(PM_PMCR_CFBVGA, PM_PMCR);
		while ((readl(PM_PLLDFCDONE) & PM_PLLDFCDONE_VGADFC)
				!= PM_PLLDFCDONE_VGADFC)
			udelay(100); /* about 1ms */

		/* set div cfg reg. */
		writel(readl(PM_PCGR) | PM_PCGR_VGACLK, PM_PCGR);

		writel((readl(PM_DIVCFG) & ~PM_DIVCFG_VGACLK_MASK)
				| PM_DIVCFG_VGACLK(pll_vgadiv), PM_DIVCFG);

		writel(readl(PM_SWRESET) | PM_SWRESET_VGADIV, PM_SWRESET);
		while ((readl(PM_SWRESET) & PM_SWRESET_VGADIV)
				== PM_SWRESET_VGADIV)
			udelay(100); /* 65536 bclk32, about 320us */

		writel(readl(PM_PCGR) & ~PM_PCGR_VGACLK, PM_PCGR);
	}
#ifdef CONFIG_CPU_FREQ
	if (clk == &clk_mclk_clk) {
		u32 pll_rate, divstatus = readl(PM_DIVSTATUS);
		int ret, i;

		/* lookup mclk_clk_table */
		ret = -EINVAL;
		for (i = 0; i < ARRAY_SIZE(mclk_clk_table); i++) {
			if (rate == mclk_clk_table[i].mrate) {
				pll_rate = mclk_clk_table[i].prate;
				clk_mclk_clk.rate = mclk_clk_table[i].mrate;
				ret = 0;
				break;
			}
		}

		if (ret)
			return ret;

		if (clk_mclk_clk.rate)
			clk_bclk32_clk.rate = clk_mclk_clk.rate
				/ (((divstatus & 0x0000f000) >> 12) + 1);

		/* set pll sys cfg reg. */
		writel(pll_rate, PM_PLLSYSCFG);

		writel(PM_PMCR_CFBSYS, PM_PMCR);
		while ((readl(PM_PLLDFCDONE) & PM_PLLDFCDONE_SYSDFC)
				!= PM_PLLDFCDONE_SYSDFC)
			udelay(100);
			/* about 1ms */
	}
#endif
	return 0;
}