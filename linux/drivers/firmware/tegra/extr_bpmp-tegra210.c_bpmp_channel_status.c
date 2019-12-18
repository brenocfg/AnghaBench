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
struct tegra_bpmp {struct tegra210_bpmp* priv; } ;
struct tegra210_bpmp {scalar_t__ arb_sema; } ;

/* Variables and functions */
 int CH_MASK (unsigned int) ; 
 scalar_t__ STA_OFFSET ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static u32 bpmp_channel_status(struct tegra_bpmp *bpmp, unsigned int index)
{
	struct tegra210_bpmp *priv = bpmp->priv;

	return __raw_readl(priv->arb_sema + STA_OFFSET) & CH_MASK(index);
}