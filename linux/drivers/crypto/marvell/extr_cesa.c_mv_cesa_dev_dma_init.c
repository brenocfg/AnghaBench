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
struct mv_cesa_tdma_desc {int dummy; } ;
struct mv_cesa_op_ctx {int dummy; } ;
struct mv_cesa_dev_dma {void* padding_pool; void* cache_pool; void* op_pool; void* tdma_desc_pool; } ;
struct mv_cesa_dev {struct mv_cesa_dev_dma* dma; TYPE_1__* caps; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_tdma; } ;

/* Variables and functions */
 int CESA_MAX_HASH_BLOCK_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mv_cesa_dev_dma* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* dmam_pool_create (char*,struct device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_dev_dma_init(struct mv_cesa_dev *cesa)
{
	struct device *dev = cesa->dev;
	struct mv_cesa_dev_dma *dma;

	if (!cesa->caps->has_tdma)
		return 0;

	dma = devm_kzalloc(dev, sizeof(*dma), GFP_KERNEL);
	if (!dma)
		return -ENOMEM;

	dma->tdma_desc_pool = dmam_pool_create("tdma_desc", dev,
					sizeof(struct mv_cesa_tdma_desc),
					16, 0);
	if (!dma->tdma_desc_pool)
		return -ENOMEM;

	dma->op_pool = dmam_pool_create("cesa_op", dev,
					sizeof(struct mv_cesa_op_ctx), 16, 0);
	if (!dma->op_pool)
		return -ENOMEM;

	dma->cache_pool = dmam_pool_create("cesa_cache", dev,
					   CESA_MAX_HASH_BLOCK_SIZE, 1, 0);
	if (!dma->cache_pool)
		return -ENOMEM;

	dma->padding_pool = dmam_pool_create("cesa_padding", dev, 72, 1, 0);
	if (!dma->padding_pool)
		return -ENOMEM;

	cesa->dma = dma;

	return 0;
}