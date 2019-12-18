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
typedef  int /*<<< orphan*/  u16 ;
struct admhcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fmnumber; } ;

/* Variables and functions */
 int ADMHC_SFN_FN_MASK ; 
 int admhc_readl (struct admhcd const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 admhc_frame_no(const struct admhcd *ahcd)
{
	u32	t;

	t = admhc_readl(ahcd, &ahcd->regs->fmnumber) & ADMHC_SFN_FN_MASK;
	return (u16)t;
}