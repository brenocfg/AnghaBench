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
struct TYPE_2__ {int /*<<< orphan*/ * sg; int /*<<< orphan*/  nents; } ;
struct atmel_aes_dev {int /*<<< orphan*/  total; int /*<<< orphan*/  buf; int /*<<< orphan*/  real_dst; int /*<<< orphan*/  aligned_sg; TYPE_1__ dst; TYPE_1__ src; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  atmel_aes_restore_sg (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_aes_unmap(struct atmel_aes_dev *dd)
{
	if (dd->src.sg == dd->dst.sg) {
		dma_unmap_sg(dd->dev, dd->src.sg, dd->src.nents,
			     DMA_BIDIRECTIONAL);

		if (dd->src.sg != &dd->aligned_sg)
			atmel_aes_restore_sg(&dd->src);
	} else {
		dma_unmap_sg(dd->dev, dd->dst.sg, dd->dst.nents,
			     DMA_FROM_DEVICE);

		if (dd->dst.sg != &dd->aligned_sg)
			atmel_aes_restore_sg(&dd->dst);

		dma_unmap_sg(dd->dev, dd->src.sg, dd->src.nents,
			     DMA_TO_DEVICE);

		if (dd->src.sg != &dd->aligned_sg)
			atmel_aes_restore_sg(&dd->src);
	}

	if (dd->dst.sg == &dd->aligned_sg)
		sg_copy_from_buffer(dd->real_dst, sg_nents(dd->real_dst),
				    dd->buf, dd->total);
}