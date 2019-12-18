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
struct zx_dma_dev {int /*<<< orphan*/  pool; } ;
struct zx_dma_desc_sw {int desc_num; int /*<<< orphan*/  desc_hw; int /*<<< orphan*/  desc_hw_lli; } ;
struct zx_dma_chan {int /*<<< orphan*/  vc; } ;
struct zx_desc_hw {int dummy; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int LLI_BLOCK_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zx_dma_desc_sw*) ; 
 struct zx_dma_desc_sw* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct zx_dma_chan* to_zx_chan (struct dma_chan*) ; 
 struct zx_dma_dev* to_zx_dma (TYPE_1__*) ; 

__attribute__((used)) static struct zx_dma_desc_sw *zx_alloc_desc_resource(int num,
						     struct dma_chan *chan)
{
	struct zx_dma_chan *c = to_zx_chan(chan);
	struct zx_dma_desc_sw *ds;
	struct zx_dma_dev *d = to_zx_dma(chan->device);
	int lli_limit = LLI_BLOCK_SIZE / sizeof(struct zx_desc_hw);

	if (num > lli_limit) {
		dev_dbg(chan->device->dev, "vch %p: sg num %d exceed max %d\n",
			&c->vc, num, lli_limit);
		return NULL;
	}

	ds = kzalloc(sizeof(*ds), GFP_ATOMIC);
	if (!ds)
		return NULL;

	ds->desc_hw = dma_pool_zalloc(d->pool, GFP_NOWAIT, &ds->desc_hw_lli);
	if (!ds->desc_hw) {
		dev_dbg(chan->device->dev, "vch %p: dma alloc fail\n", &c->vc);
		kfree(ds);
		return NULL;
	}
	ds->desc_num = num;
	return ds;
}