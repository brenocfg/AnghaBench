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
struct admhcd {int fminterval; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fminterval; } ;

/* Variables and functions */
 int ADMHC_SFI_FI_MASK ; 
 int FIT ; 
 int admhc_readl (struct admhcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  admhc_writel (struct admhcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void periodic_reinit(struct admhcd *ahcd)
{
#if 0
	u32	fi = ahcd->fminterval & ADMHC_SFI_FI_MASK;
	u32	fit = admhc_readl(ahcd, &ahcd->regs->fminterval) & FIT;

	/* TODO: adjust FSLargestDataPacket value too? */
	admhc_writel(ahcd, (fit ^ FIT) | ahcd->fminterval,
					&ahcd->regs->fminterval);
#else
	u32	fit = admhc_readl(ahcd, &ahcd->regs->fminterval) & FIT;

	/* TODO: adjust FSLargestDataPacket value too? */
	admhc_writel(ahcd, (fit ^ FIT) | ahcd->fminterval,
					&ahcd->regs->fminterval);
#endif
}