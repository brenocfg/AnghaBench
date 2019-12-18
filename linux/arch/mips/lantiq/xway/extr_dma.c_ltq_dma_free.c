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
struct ltq_dma_channel {int /*<<< orphan*/  phys; int /*<<< orphan*/  desc_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LTQ_DESC_NUM ; 
 int LTQ_DESC_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_close (struct ltq_dma_channel*) ; 

void
ltq_dma_free(struct ltq_dma_channel *ch)
{
	if (!ch->desc_base)
		return;
	ltq_dma_close(ch);
	dma_free_coherent(ch->dev, LTQ_DESC_NUM * LTQ_DESC_SIZE,
		ch->desc_base, ch->phys);
}