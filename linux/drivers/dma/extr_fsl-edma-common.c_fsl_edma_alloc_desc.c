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
struct fsl_edma_desc {int n_tcds; TYPE_1__* tcd; struct fsl_edma_chan* echan; } ;
struct fsl_edma_chan {int /*<<< orphan*/  tcd_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptcd; int /*<<< orphan*/  vtcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsl_edma_desc*) ; 
 struct fsl_edma_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct fsl_edma_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcd ; 

__attribute__((used)) static struct fsl_edma_desc *fsl_edma_alloc_desc(struct fsl_edma_chan *fsl_chan,
		int sg_len)
{
	struct fsl_edma_desc *fsl_desc;
	int i;

	fsl_desc = kzalloc(struct_size(fsl_desc, tcd, sg_len), GFP_NOWAIT);
	if (!fsl_desc)
		return NULL;

	fsl_desc->echan = fsl_chan;
	fsl_desc->n_tcds = sg_len;
	for (i = 0; i < sg_len; i++) {
		fsl_desc->tcd[i].vtcd = dma_pool_alloc(fsl_chan->tcd_pool,
					GFP_NOWAIT, &fsl_desc->tcd[i].ptcd);
		if (!fsl_desc->tcd[i].vtcd)
			goto err;
	}
	return fsl_desc;

err:
	while (--i >= 0)
		dma_pool_free(fsl_chan->tcd_pool, fsl_desc->tcd[i].vtcd,
				fsl_desc->tcd[i].ptcd);
	kfree(fsl_desc);
	return NULL;
}