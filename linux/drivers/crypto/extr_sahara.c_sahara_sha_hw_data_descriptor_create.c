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
struct sahara_sha_reqctx {scalar_t__ total; int sg_in_idx; unsigned int context_size; scalar_t__ first; } ;
struct sahara_dev {TYPE_2__** hw_link; TYPE_1__** hw_desc; int /*<<< orphan*/  context_phys_base; scalar_t__* hw_phys_link; } ;
struct ahash_request {int dummy; } ;
struct TYPE_4__ {unsigned int len; scalar_t__ next; int /*<<< orphan*/  p; } ;
struct TYPE_3__ {scalar_t__ len1; unsigned int len2; scalar_t__ p2; scalar_t__ p1; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAHARA_HDR_MDHA_HASH ; 
 int sahara_sha_hw_links_create (struct sahara_dev*,struct sahara_sha_reqctx*,int) ; 
 int /*<<< orphan*/  sahara_sha_init_hdr (struct sahara_dev*,struct sahara_sha_reqctx*) ; 

__attribute__((used)) static int sahara_sha_hw_data_descriptor_create(struct sahara_dev *dev,
						struct sahara_sha_reqctx *rctx,
						struct ahash_request *req,
						int index)
{
	unsigned result_len;
	int i = index;

	if (rctx->first)
		/* Create initial descriptor: #8*/
		dev->hw_desc[index]->hdr = sahara_sha_init_hdr(dev, rctx);
	else
		/* Create hash descriptor: #10. Must follow #6. */
		dev->hw_desc[index]->hdr = SAHARA_HDR_MDHA_HASH;

	dev->hw_desc[index]->len1 = rctx->total;
	if (dev->hw_desc[index]->len1 == 0) {
		/* if len1 is 0, p1 must be 0, too */
		dev->hw_desc[index]->p1 = 0;
		rctx->sg_in_idx = 0;
	} else {
		/* Create input links */
		dev->hw_desc[index]->p1 = dev->hw_phys_link[index];
		i = sahara_sha_hw_links_create(dev, rctx, index);

		rctx->sg_in_idx = index;
		if (i < 0)
			return i;
	}

	dev->hw_desc[index]->p2 = dev->hw_phys_link[i];

	/* Save the context for the next operation */
	result_len = rctx->context_size;
	dev->hw_link[i]->p = dev->context_phys_base;

	dev->hw_link[i]->len = result_len;
	dev->hw_desc[index]->len2 = result_len;

	dev->hw_link[i]->next = 0;

	return 0;
}