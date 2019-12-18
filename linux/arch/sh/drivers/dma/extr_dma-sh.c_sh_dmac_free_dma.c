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
struct dma_channel {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dma_channel*) ; 
 int /*<<< orphan*/  get_dmte_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_dmac_free_dma(struct dma_channel *chan)
{
	free_irq(get_dmte_irq(chan->chan), chan);
}