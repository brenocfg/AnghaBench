#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {unsigned int count; } ;
struct tegra_bpmp {TYPE_10__* tx_channel; TYPE_10__* rx_channel; TYPE_10__* threaded_channels; TYPE_7__ threaded; TYPE_14__* dev; TYPE_5__* soc; struct tegra186_bpmp* priv; } ;
struct TYPE_27__ {void* virt; void* pool; int /*<<< orphan*/  phys; } ;
struct TYPE_26__ {void* virt; void* pool; int /*<<< orphan*/  phys; } ;
struct TYPE_17__ {int tx_block; int knows_txdone; int /*<<< orphan*/  rx_callback; TYPE_14__* dev; } ;
struct TYPE_24__ {int /*<<< orphan*/  channel; TYPE_13__ client; } ;
struct tegra186_bpmp {TYPE_9__ tx; TYPE_8__ rx; TYPE_6__ mbox; struct tegra_bpmp* parent; } ;
struct TYPE_21__ {unsigned int offset; } ;
struct TYPE_20__ {unsigned int offset; } ;
struct TYPE_19__ {unsigned int offset; } ;
struct TYPE_22__ {TYPE_3__ thread; TYPE_2__ cpu_rx; TYPE_1__ cpu_tx; } ;
struct TYPE_23__ {TYPE_4__ channels; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_16__ {int /*<<< orphan*/  bpmp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_14__*,char*,...) ; 
 struct tegra186_bpmp* devm_kzalloc (TYPE_14__*,int,int /*<<< orphan*/ ) ; 
 void* gen_pool_dma_alloc (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_pool_free (void*,unsigned long,int) ; 
 int /*<<< orphan*/  mbox_handle_rx ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_13__*,int /*<<< orphan*/ ) ; 
 void* of_gen_pool_get (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tegra186_bpmp_channel_cleanup (TYPE_10__*) ; 
 int tegra186_bpmp_channel_init (TYPE_10__*,struct tegra_bpmp*,unsigned int) ; 
 int /*<<< orphan*/  tegra186_bpmp_channel_reset (TYPE_10__*) ; 

__attribute__((used)) static int tegra186_bpmp_init(struct tegra_bpmp *bpmp)
{
	struct tegra186_bpmp *priv;
	unsigned int i;
	int err;

	priv = devm_kzalloc(bpmp->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	bpmp->priv = priv;
	priv->parent = bpmp;

	priv->tx.pool = of_gen_pool_get(bpmp->dev->of_node, "shmem", 0);
	if (!priv->tx.pool) {
		dev_err(bpmp->dev, "TX shmem pool not found\n");
		return -ENOMEM;
	}

	priv->tx.virt = gen_pool_dma_alloc(priv->tx.pool, 4096, &priv->tx.phys);
	if (!priv->tx.virt) {
		dev_err(bpmp->dev, "failed to allocate from TX pool\n");
		return -ENOMEM;
	}

	priv->rx.pool = of_gen_pool_get(bpmp->dev->of_node, "shmem", 1);
	if (!priv->rx.pool) {
		dev_err(bpmp->dev, "RX shmem pool not found\n");
		err = -ENOMEM;
		goto free_tx;
	}

	priv->rx.virt = gen_pool_dma_alloc(priv->rx.pool, 4096, &priv->rx.phys);
	if (!priv->rx.virt) {
		dev_err(bpmp->dev, "failed to allocate from RX pool\n");
		err = -ENOMEM;
		goto free_tx;
	}

	err = tegra186_bpmp_channel_init(bpmp->tx_channel, bpmp,
					 bpmp->soc->channels.cpu_tx.offset);
	if (err < 0)
		goto free_rx;

	err = tegra186_bpmp_channel_init(bpmp->rx_channel, bpmp,
					 bpmp->soc->channels.cpu_rx.offset);
	if (err < 0)
		goto cleanup_tx_channel;

	for (i = 0; i < bpmp->threaded.count; i++) {
		unsigned int index = bpmp->soc->channels.thread.offset + i;

		err = tegra186_bpmp_channel_init(&bpmp->threaded_channels[i],
						 bpmp, index);
		if (err < 0)
			goto cleanup_channels;
	}

	/* mbox registration */
	priv->mbox.client.dev = bpmp->dev;
	priv->mbox.client.rx_callback = mbox_handle_rx;
	priv->mbox.client.tx_block = false;
	priv->mbox.client.knows_txdone = false;

	priv->mbox.channel = mbox_request_channel(&priv->mbox.client, 0);
	if (IS_ERR(priv->mbox.channel)) {
		err = PTR_ERR(priv->mbox.channel);
		dev_err(bpmp->dev, "failed to get HSP mailbox: %d\n", err);
		goto cleanup_channels;
	}

	tegra186_bpmp_channel_reset(bpmp->tx_channel);
	tegra186_bpmp_channel_reset(bpmp->rx_channel);

	for (i = 0; i < bpmp->threaded.count; i++)
		tegra186_bpmp_channel_reset(&bpmp->threaded_channels[i]);

	return 0;

cleanup_channels:
	for (i = 0; i < bpmp->threaded.count; i++) {
		if (!bpmp->threaded_channels[i].bpmp)
			continue;

		tegra186_bpmp_channel_cleanup(&bpmp->threaded_channels[i]);
	}

	tegra186_bpmp_channel_cleanup(bpmp->rx_channel);
cleanup_tx_channel:
	tegra186_bpmp_channel_cleanup(bpmp->tx_channel);
free_rx:
	gen_pool_free(priv->rx.pool, (unsigned long)priv->rx.virt, 4096);
free_tx:
	gen_pool_free(priv->tx.pool, (unsigned long)priv->tx.virt, 4096);

	return err;
}