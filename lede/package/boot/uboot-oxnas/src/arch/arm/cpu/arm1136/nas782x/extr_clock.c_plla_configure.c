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

/* Variables and functions */
 int PLL_BWADJ_SHIFT ; 
 int PLL_BYPASS ; 
 int PLL_OUTDIV_SHIFT ; 
 int PLL_REFDIV_SHIFT ; 
 int SAT_ENABLE ; 
 int /*<<< orphan*/  SYS_CTRL_PLLA_CTRL0 ; 
 int /*<<< orphan*/  SYS_CTRL_PLLA_CTRL1 ; 
 int /*<<< orphan*/  SYS_CTRL_PLLA_CTRL2 ; 
 int /*<<< orphan*/  SYS_CTRL_PLLA_CTRL3 ; 
 int /*<<< orphan*/  SYS_CTRL_RST_PLLA ; 
 int /*<<< orphan*/  clrbits_le32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_block (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbits_le32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plla_configure(int outdiv, int refdiv, int fbdiv, int bwadj,
                           int sfreq, int sslope)
{
	setbits_le32(SYS_CTRL_PLLA_CTRL0, PLL_BYPASS);
	udelay(10);
	reset_block(SYS_CTRL_RST_PLLA, 1);
	udelay(10);

	writel((refdiv << PLL_REFDIV_SHIFT) | (outdiv << PLL_OUTDIV_SHIFT) |
	       SAT_ENABLE | PLL_BYPASS,
	       SYS_CTRL_PLLA_CTRL0);

	writel(fbdiv, SYS_CTRL_PLLA_CTRL1);
	writel((bwadj << PLL_BWADJ_SHIFT) | sfreq, SYS_CTRL_PLLA_CTRL2);
	writel(sslope, SYS_CTRL_PLLA_CTRL3);

	udelay(10); // 5us delay required (from TCI datasheet), use 10us

	reset_block(SYS_CTRL_RST_PLLA, 0);

	udelay(100); // Delay for PLL to lock

	printf("  plla_ctrl0 : %08x\n", readl(SYS_CTRL_PLLA_CTRL0));
	printf("  plla_ctrl1 : %08x\n", readl(SYS_CTRL_PLLA_CTRL1));
	printf("  plla_ctrl2 : %08x\n", readl(SYS_CTRL_PLLA_CTRL2));
	printf("  plla_ctrl3 : %08x\n", readl(SYS_CTRL_PLLA_CTRL3));

	clrbits_le32(SYS_CTRL_PLLA_CTRL0, PLL_BYPASS); // Take PLL out of bypass
	puts("\nPLLA Set\n");
}