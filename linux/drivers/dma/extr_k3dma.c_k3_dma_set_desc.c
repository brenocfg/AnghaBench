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
struct k3_dma_phy {scalar_t__ base; } ;
struct k3_desc_hw {int /*<<< orphan*/  config; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  count; int /*<<< orphan*/  lli; } ;

/* Variables and functions */
 scalar_t__ CX_CFG ; 
 scalar_t__ CX_CNT0 ; 
 scalar_t__ CX_DST ; 
 scalar_t__ CX_LLI ; 
 scalar_t__ CX_SRC ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void k3_dma_set_desc(struct k3_dma_phy *phy, struct k3_desc_hw *hw)
{
	writel_relaxed(hw->lli, phy->base + CX_LLI);
	writel_relaxed(hw->count, phy->base + CX_CNT0);
	writel_relaxed(hw->saddr, phy->base + CX_SRC);
	writel_relaxed(hw->daddr, phy->base + CX_DST);
	writel_relaxed(hw->config, phy->base + CX_CFG);
}