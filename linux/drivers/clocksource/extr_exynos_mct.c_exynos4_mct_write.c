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

/* Variables and functions */
#define  EXYNOS4_MCT_G_CNT_L 136 
#define  EXYNOS4_MCT_G_CNT_U 135 
 unsigned long EXYNOS4_MCT_G_CNT_WSTAT ; 
#define  EXYNOS4_MCT_G_COMP0_ADD_INCR 134 
#define  EXYNOS4_MCT_G_COMP0_L 133 
#define  EXYNOS4_MCT_G_COMP0_U 132 
#define  EXYNOS4_MCT_G_TCON 131 
 unsigned long EXYNOS4_MCT_G_WSTAT ; 
 unsigned long EXYNOS4_MCT_L_BASE (int /*<<< orphan*/ ) ; 
 unsigned long EXYNOS4_MCT_L_MASK ; 
 int HZ ; 
#define  MCT_L_ICNTB_OFFSET 130 
#define  MCT_L_TCNTB_OFFSET 129 
#define  MCT_L_TCON_OFFSET 128 
 unsigned long MCT_L_WSTAT_OFFSET ; 
 scalar_t__ likely (int) ; 
 int loops_per_jiffy ; 
 int /*<<< orphan*/  panic (char*,unsigned int,unsigned long) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ reg_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void exynos4_mct_write(unsigned int value, unsigned long offset)
{
	unsigned long stat_addr;
	u32 mask;
	u32 i;

	writel_relaxed(value, reg_base + offset);

	if (likely(offset >= EXYNOS4_MCT_L_BASE(0))) {
		stat_addr = (offset & EXYNOS4_MCT_L_MASK) + MCT_L_WSTAT_OFFSET;
		switch (offset & ~EXYNOS4_MCT_L_MASK) {
		case MCT_L_TCON_OFFSET:
			mask = 1 << 3;		/* L_TCON write status */
			break;
		case MCT_L_ICNTB_OFFSET:
			mask = 1 << 1;		/* L_ICNTB write status */
			break;
		case MCT_L_TCNTB_OFFSET:
			mask = 1 << 0;		/* L_TCNTB write status */
			break;
		default:
			return;
		}
	} else {
		switch (offset) {
		case EXYNOS4_MCT_G_TCON:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 16;		/* G_TCON write status */
			break;
		case EXYNOS4_MCT_G_COMP0_L:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 0;		/* G_COMP0_L write status */
			break;
		case EXYNOS4_MCT_G_COMP0_U:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 1;		/* G_COMP0_U write status */
			break;
		case EXYNOS4_MCT_G_COMP0_ADD_INCR:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 2;		/* G_COMP0_ADD_INCR w status */
			break;
		case EXYNOS4_MCT_G_CNT_L:
			stat_addr = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 0;		/* G_CNT_L write status */
			break;
		case EXYNOS4_MCT_G_CNT_U:
			stat_addr = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 1;		/* G_CNT_U write status */
			break;
		default:
			return;
		}
	}

	/* Wait maximum 1 ms until written values are applied */
	for (i = 0; i < loops_per_jiffy / 1000 * HZ; i++)
		if (readl_relaxed(reg_base + stat_addr) & mask) {
			writel_relaxed(mask, reg_base + stat_addr);
			return;
		}

	panic("MCT hangs after writing %d (offset:0x%lx)\n", value, offset);
}