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
struct atmel_tdes_dev {int flags; size_t dma_size; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf_out; int /*<<< orphan*/  out_offset; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  dma_addr_out; int /*<<< orphan*/  dev; int /*<<< orphan*/  in_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int TDES_FLAGS_DMA ; 
 int TDES_FLAGS_FAST ; 
 size_t atmel_tdes_sg_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

__attribute__((used)) static int atmel_tdes_crypt_dma_stop(struct atmel_tdes_dev *dd)
{
	int err = -EINVAL;
	size_t count;

	if (dd->flags & TDES_FLAGS_DMA) {
		err = 0;
		if  (dd->flags & TDES_FLAGS_FAST) {
			dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_FROM_DEVICE);
			dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		} else {
			dma_sync_single_for_device(dd->dev, dd->dma_addr_out,
				dd->dma_size, DMA_FROM_DEVICE);

			/* copy data */
			count = atmel_tdes_sg_copy(&dd->out_sg, &dd->out_offset,
				dd->buf_out, dd->buflen, dd->dma_size, 1);
			if (count != dd->dma_size) {
				err = -EINVAL;
				pr_err("not all data converted: %zu\n", count);
			}
		}
	}
	return err;
}