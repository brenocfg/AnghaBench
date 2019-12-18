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
struct atmel_tdes_dev {scalar_t__ buf_in; scalar_t__ buf_out; int /*<<< orphan*/  buflen; int /*<<< orphan*/  dma_addr_in; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_addr_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void atmel_tdes_buff_cleanup(struct atmel_tdes_dev *dd)
{
	dma_unmap_single(dd->dev, dd->dma_addr_out, dd->buflen,
			 DMA_FROM_DEVICE);
	dma_unmap_single(dd->dev, dd->dma_addr_in, dd->buflen,
		DMA_TO_DEVICE);
	free_page((unsigned long)dd->buf_out);
	free_page((unsigned long)dd->buf_in);
}