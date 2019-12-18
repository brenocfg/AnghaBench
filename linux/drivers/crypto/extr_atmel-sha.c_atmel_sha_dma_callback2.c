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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct atmel_sha_dma {int nents; int /*<<< orphan*/  last_sg_length; struct scatterlist* sg; int /*<<< orphan*/  chan; } ;
struct atmel_sha_dev {int is_async; int /*<<< orphan*/  resume; int /*<<< orphan*/  dev; struct atmel_sha_dma dma_lch_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  atmel_sha_wait_for_data_ready (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static void atmel_sha_dma_callback2(void *data)
{
	struct atmel_sha_dev *dd = data;
	struct atmel_sha_dma *dma = &dd->dma_lch_in;
	struct scatterlist *sg;
	int nents;

	dmaengine_terminate_all(dma->chan);
	dma_unmap_sg(dd->dev, dma->sg, dma->nents, DMA_TO_DEVICE);

	sg = dma->sg;
	for (nents = 0; nents < dma->nents - 1; ++nents)
		sg = sg_next(sg);
	sg->length = dma->last_sg_length;

	dd->is_async = true;
	(void)atmel_sha_wait_for_data_ready(dd, dd->resume);
}