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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_bpmp_channel {unsigned int index; struct tegra_bpmp* bpmp; int /*<<< orphan*/  completion; void* ob; void* ib; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; struct tegra210_bpmp* priv; } ;
struct tegra210_bpmp {scalar_t__ atomics; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ RESULT_OFFSET (unsigned int) ; 
 unsigned int TRIGGER_CMD_GET ; 
 unsigned int TRIGGER_ID_SHIFT ; 
 scalar_t__ TRIGGER_OFFSET ; 
 void* devm_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int tegra210_bpmp_channel_init(struct tegra_bpmp_channel *channel,
				      struct tegra_bpmp *bpmp,
				      unsigned int index)
{
	struct tegra210_bpmp *priv = bpmp->priv;
	u32 address;
	void *p;

	/* Retrieve channel base address from BPMP */
	writel(index << TRIGGER_ID_SHIFT | TRIGGER_CMD_GET,
	       priv->atomics + TRIGGER_OFFSET);
	address = readl(priv->atomics + RESULT_OFFSET(index));

	p = devm_ioremap(bpmp->dev, address, 0x80);
	if (!p)
		return -ENOMEM;

	channel->ib = p;
	channel->ob = p;
	channel->index = index;
	init_completion(&channel->completion);
	channel->bpmp = bpmp;

	return 0;
}