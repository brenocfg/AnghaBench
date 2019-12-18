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
struct dma_device {int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_prep_dma_interrupt; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  channels; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  directions; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  dev; } ;
struct dma_chan {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct ccp_dma_desc {int dummy; } ;
struct ccp_dma_cmd {int dummy; } ;
struct ccp_dma_chan {int /*<<< orphan*/  cleanup_tasklet; int /*<<< orphan*/  complete; int /*<<< orphan*/  active; int /*<<< orphan*/  pending; int /*<<< orphan*/  created; int /*<<< orphan*/  lock; struct ccp_device* ccp; struct dma_chan dma_chan; } ;
struct ccp_device {unsigned int cmd_q_count; void* dma_cmd_cache; void* dma_desc_cache; struct ccp_dma_chan* ccp_dma_chan; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; struct dma_device dma_dev; } ;

/* Variables and functions */
 void* CCP_DMA_WIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_INTERRUPT ; 
 scalar_t__ DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 scalar_t__ DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_DESCRIPTOR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  ccp_do_cleanup ; 
 int /*<<< orphan*/  ccp_free_chan_resources ; 
 scalar_t__ ccp_get_dma_chan_attr (struct ccp_device*) ; 
 int /*<<< orphan*/  ccp_issue_pending ; 
 int /*<<< orphan*/  ccp_pause ; 
 int /*<<< orphan*/  ccp_prep_dma_interrupt ; 
 int /*<<< orphan*/  ccp_prep_dma_memcpy ; 
 int /*<<< orphan*/  ccp_resume ; 
 int /*<<< orphan*/  ccp_terminate_all ; 
 int /*<<< orphan*/  ccp_tx_status ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ccp_dma_chan* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_get_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine ; 
 void* kmem_cache_create (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int ccp_dmaengine_register(struct ccp_device *ccp)
{
	struct ccp_dma_chan *chan;
	struct dma_device *dma_dev = &ccp->dma_dev;
	struct dma_chan *dma_chan;
	char *dma_cmd_cache_name;
	char *dma_desc_cache_name;
	unsigned int i;
	int ret;

	if (!dmaengine)
		return 0;

	ccp->ccp_dma_chan = devm_kcalloc(ccp->dev, ccp->cmd_q_count,
					 sizeof(*(ccp->ccp_dma_chan)),
					 GFP_KERNEL);
	if (!ccp->ccp_dma_chan)
		return -ENOMEM;

	dma_cmd_cache_name = devm_kasprintf(ccp->dev, GFP_KERNEL,
					    "%s-dmaengine-cmd-cache",
					    ccp->name);
	if (!dma_cmd_cache_name)
		return -ENOMEM;

	ccp->dma_cmd_cache = kmem_cache_create(dma_cmd_cache_name,
					       sizeof(struct ccp_dma_cmd),
					       sizeof(void *),
					       SLAB_HWCACHE_ALIGN, NULL);
	if (!ccp->dma_cmd_cache)
		return -ENOMEM;

	dma_desc_cache_name = devm_kasprintf(ccp->dev, GFP_KERNEL,
					     "%s-dmaengine-desc-cache",
					     ccp->name);
	if (!dma_desc_cache_name) {
		ret = -ENOMEM;
		goto err_cache;
	}

	ccp->dma_desc_cache = kmem_cache_create(dma_desc_cache_name,
						sizeof(struct ccp_dma_desc),
						sizeof(void *),
						SLAB_HWCACHE_ALIGN, NULL);
	if (!ccp->dma_desc_cache) {
		ret = -ENOMEM;
		goto err_cache;
	}

	dma_dev->dev = ccp->dev;
	dma_dev->src_addr_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->dst_addr_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->directions = DMA_MEM_TO_MEM;
	dma_dev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_INTERRUPT, dma_dev->cap_mask);

	/* The DMA channels for this device can be set to public or private,
	 * and overridden by the module parameter dma_chan_attr.
	 * Default: according to the value in vdata (dma_chan_attr=0)
	 * dma_chan_attr=0x1: all channels private (override vdata)
	 * dma_chan_attr=0x2: all channels public (override vdata)
	 */
	if (ccp_get_dma_chan_attr(ccp) == DMA_PRIVATE)
		dma_cap_set(DMA_PRIVATE, dma_dev->cap_mask);

	INIT_LIST_HEAD(&dma_dev->channels);
	for (i = 0; i < ccp->cmd_q_count; i++) {
		chan = ccp->ccp_dma_chan + i;
		dma_chan = &chan->dma_chan;

		chan->ccp = ccp;

		spin_lock_init(&chan->lock);
		INIT_LIST_HEAD(&chan->created);
		INIT_LIST_HEAD(&chan->pending);
		INIT_LIST_HEAD(&chan->active);
		INIT_LIST_HEAD(&chan->complete);

		tasklet_init(&chan->cleanup_tasklet, ccp_do_cleanup,
			     (unsigned long)chan);

		dma_chan->device = dma_dev;
		dma_cookie_init(dma_chan);

		list_add_tail(&dma_chan->device_node, &dma_dev->channels);
	}

	dma_dev->device_free_chan_resources = ccp_free_chan_resources;
	dma_dev->device_prep_dma_memcpy = ccp_prep_dma_memcpy;
	dma_dev->device_prep_dma_interrupt = ccp_prep_dma_interrupt;
	dma_dev->device_issue_pending = ccp_issue_pending;
	dma_dev->device_tx_status = ccp_tx_status;
	dma_dev->device_pause = ccp_pause;
	dma_dev->device_resume = ccp_resume;
	dma_dev->device_terminate_all = ccp_terminate_all;

	ret = dma_async_device_register(dma_dev);
	if (ret)
		goto err_reg;

	return 0;

err_reg:
	kmem_cache_destroy(ccp->dma_desc_cache);

err_cache:
	kmem_cache_destroy(ccp->dma_cmd_cache);

	return ret;
}