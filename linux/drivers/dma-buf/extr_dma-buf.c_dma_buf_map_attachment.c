#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct dma_buf_attachment {int dir; struct sg_table* sgt; TYPE_2__* dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ cache_sgt_mapping; struct sg_table* (* map_dma_buf ) (struct dma_buf_attachment*,int) ;} ;

/* Variables and functions */
 scalar_t__ DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct sg_table*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 struct sg_table* stub1 (struct dma_buf_attachment*,int) ; 

struct sg_table *dma_buf_map_attachment(struct dma_buf_attachment *attach,
					enum dma_data_direction direction)
{
	struct sg_table *sg_table;

	might_sleep();

	if (WARN_ON(!attach || !attach->dmabuf))
		return ERR_PTR(-EINVAL);

	if (attach->sgt) {
		/*
		 * Two mappings with different directions for the same
		 * attachment are not allowed.
		 */
		if (attach->dir != direction &&
		    attach->dir != DMA_BIDIRECTIONAL)
			return ERR_PTR(-EBUSY);

		return attach->sgt;
	}

	sg_table = attach->dmabuf->ops->map_dma_buf(attach, direction);
	if (!sg_table)
		sg_table = ERR_PTR(-ENOMEM);

	if (!IS_ERR(sg_table) && attach->dmabuf->ops->cache_sgt_mapping) {
		attach->sgt = sg_table;
		attach->dir = direction;
	}

	return sg_table;
}