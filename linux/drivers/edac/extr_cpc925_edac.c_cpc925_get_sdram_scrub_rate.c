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
typedef  int u8 ;
typedef  int u32 ;
struct mem_ctl_info {struct cpc925_mc_pdata* pvt_info; } ;
struct cpc925_mc_pdata {scalar_t__ vbase; } ;

/* Variables and functions */
 int CPC925_SCRUB_BLOCK_SIZE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MSCR_BACKGR_SCRUB ; 
 int MSCR_SCRUB_MOD_MASK ; 
 int MSCR_SI_MASK ; 
 int MSCR_SI_SHIFT ; 
 scalar_t__ REG_MSCR_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  cpc925_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cpc925_get_sdram_scrub_rate(struct mem_ctl_info *mci)
{
	struct cpc925_mc_pdata *pdata = mci->pvt_info;
	int bw;
	u32 mscr;
	u8 si;

	mscr = __raw_readl(pdata->vbase + REG_MSCR_OFFSET);
	si = (mscr & MSCR_SI_MASK) >> MSCR_SI_SHIFT;

	edac_dbg(0, "Mem Scrub Ctrl Register 0x%x\n", mscr);

	if (((mscr & MSCR_SCRUB_MOD_MASK) != MSCR_BACKGR_SCRUB) ||
	    (si == 0)) {
		cpc925_mc_printk(mci, KERN_INFO, "Scrub mode not enabled\n");
		bw = 0;
	} else
		bw = CPC925_SCRUB_BLOCK_SIZE * 0xFA67 / si;

	return bw;
}