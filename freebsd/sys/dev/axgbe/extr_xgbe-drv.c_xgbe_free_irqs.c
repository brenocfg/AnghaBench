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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  dev; struct xgbe_channel* channel; int /*<<< orphan*/  per_channel_irq; int /*<<< orphan*/  dev_irq_tag; int /*<<< orphan*/  dev_irq_res; } ;
struct xgbe_channel {int /*<<< orphan*/  dma_irq_tag; int /*<<< orphan*/  dma_irq_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_free_irqs(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	bus_teardown_intr(pdata->dev, pdata->dev_irq_res, pdata->dev_irq_tag);

	if (!pdata->per_channel_irq)
		return;

	channel = pdata->channel;
	for (i = 0; i < pdata->channel_count; i++, channel++)
		bus_teardown_intr(pdata->dev, channel->dma_irq_res,
		    channel->dma_irq_tag);
}