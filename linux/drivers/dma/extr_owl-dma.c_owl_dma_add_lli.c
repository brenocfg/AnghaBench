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
struct owl_dma_txd {int /*<<< orphan*/  lli_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrla; int /*<<< orphan*/  next_lli; } ;
struct owl_dma_lli {TYPE_1__ hw; int /*<<< orphan*/  phys; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_DMA_MODE_LME ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_hw_ctrla (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct owl_dma_lli *owl_dma_add_lli(struct owl_dma_txd *txd,
					   struct owl_dma_lli *prev,
					   struct owl_dma_lli *next,
					   bool is_cyclic)
{
	if (!is_cyclic)
		list_add_tail(&next->node, &txd->lli_list);

	if (prev) {
		prev->hw.next_lli = next->phys;
		prev->hw.ctrla |= llc_hw_ctrla(OWL_DMA_MODE_LME, 0);
	}

	return next;
}