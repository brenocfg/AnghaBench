#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tgcr; int /*<<< orphan*/  tcr; int /*<<< orphan*/  prdlo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_DEVSTATE_ENABLED ; 
 int TCR_CLKSRCLO ; 
 int TCR_ENAMODELO_MASK ; 
 int TCR_PWIDLO_MASK ; 
 int TGCR_TIMLORS ; 
 int TGCR_TIMMODE_MASK ; 
 int TGCR_TIMMODE_UD32 ; 
 int /*<<< orphan*/  dscr_set_devstate (scalar_t__,int /*<<< orphan*/ ) ; 
 int soc_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_writel (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* timer ; 
 scalar_t__ timer64_devstate_id ; 

__attribute__((used)) static void timer64_enable(void)
{
	u32 val;

	if (timer64_devstate_id >= 0)
		dscr_set_devstate(timer64_devstate_id, DSCR_DEVSTATE_ENABLED);

	/* disable timer, reset count */
	soc_writel(soc_readl(&timer->tcr) & ~TCR_ENAMODELO_MASK, &timer->tcr);
	soc_writel(0, &timer->prdlo);

	/* use internal clock and 1 cycle pulse width */
	val = soc_readl(&timer->tcr);
	soc_writel(val & ~(TCR_CLKSRCLO | TCR_PWIDLO_MASK), &timer->tcr);

	/* dual 32-bit unchained mode */
	val = soc_readl(&timer->tgcr) & ~TGCR_TIMMODE_MASK;
	soc_writel(val, &timer->tgcr);
	soc_writel(val | (TGCR_TIMLORS | TGCR_TIMMODE_UD32), &timer->tgcr);
}