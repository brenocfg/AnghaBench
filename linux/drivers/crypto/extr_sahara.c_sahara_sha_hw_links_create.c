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
struct scatterlist {int /*<<< orphan*/  dma_address; int /*<<< orphan*/  length; } ;
struct sahara_sha_reqctx {int /*<<< orphan*/  total; struct scatterlist* in_sg; } ;
struct sahara_dev {int nb_in_sg; scalar_t__* hw_phys_link; TYPE_1__** hw_link; struct scatterlist* in_sg; int /*<<< orphan*/  device; scalar_t__ nb_out_sg; } ;
struct TYPE_2__ {scalar_t__ next; int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ SAHARA_MAX_HW_LINK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int sg_nents_for_len (struct scatterlist*,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int sahara_sha_hw_links_create(struct sahara_dev *dev,
				       struct sahara_sha_reqctx *rctx,
				       int start)
{
	struct scatterlist *sg;
	unsigned int i;
	int ret;

	dev->in_sg = rctx->in_sg;

	dev->nb_in_sg = sg_nents_for_len(dev->in_sg, rctx->total);
	if (dev->nb_in_sg < 0) {
		dev_err(dev->device, "Invalid numbers of src SG.\n");
		return dev->nb_in_sg;
	}
	if ((dev->nb_in_sg) > SAHARA_MAX_HW_LINK) {
		dev_err(dev->device, "not enough hw links (%d)\n",
			dev->nb_in_sg + dev->nb_out_sg);
		return -EINVAL;
	}

	sg = dev->in_sg;
	ret = dma_map_sg(dev->device, dev->in_sg, dev->nb_in_sg, DMA_TO_DEVICE);
	if (!ret)
		return -EFAULT;

	for (i = start; i < dev->nb_in_sg + start; i++) {
		dev->hw_link[i]->len = sg->length;
		dev->hw_link[i]->p = sg->dma_address;
		if (i == (dev->nb_in_sg + start - 1)) {
			dev->hw_link[i]->next = 0;
		} else {
			dev->hw_link[i]->next = dev->hw_phys_link[i + 1];
			sg = sg_next(sg);
		}
	}

	return i;
}