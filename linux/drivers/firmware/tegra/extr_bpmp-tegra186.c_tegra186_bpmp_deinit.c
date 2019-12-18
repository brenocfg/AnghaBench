#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int count; } ;
struct tegra_bpmp {int /*<<< orphan*/ * tx_channel; int /*<<< orphan*/ * rx_channel; int /*<<< orphan*/ * threaded_channels; TYPE_1__ threaded; struct tegra186_bpmp* priv; } ;
struct TYPE_7__ {scalar_t__ virt; int /*<<< orphan*/  pool; } ;
struct TYPE_6__ {scalar_t__ virt; int /*<<< orphan*/  pool; } ;
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct tegra186_bpmp {TYPE_3__ tx; TYPE_2__ rx; TYPE_4__ mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra186_bpmp_channel_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra186_bpmp_deinit(struct tegra_bpmp *bpmp)
{
	struct tegra186_bpmp *priv = bpmp->priv;
	unsigned int i;

	mbox_free_channel(priv->mbox.channel);

	for (i = 0; i < bpmp->threaded.count; i++)
		tegra186_bpmp_channel_cleanup(&bpmp->threaded_channels[i]);

	tegra186_bpmp_channel_cleanup(bpmp->rx_channel);
	tegra186_bpmp_channel_cleanup(bpmp->tx_channel);

	gen_pool_free(priv->rx.pool, (unsigned long)priv->rx.virt, 4096);
	gen_pool_free(priv->tx.pool, (unsigned long)priv->tx.virt, 4096);
}