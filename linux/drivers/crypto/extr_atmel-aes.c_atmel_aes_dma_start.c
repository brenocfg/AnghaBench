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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_3__ {int max_burst_size; } ;
struct atmel_aes_dev {int /*<<< orphan*/  resume; TYPE_1__ caps; TYPE_2__* ctx; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
typedef  int /*<<< orphan*/  atmel_aes_fn_t ;
struct TYPE_4__ {int block_size; } ;

/* Variables and functions */
#define  AES_BLOCK_SIZE 132 
#define  CFB16_BLOCK_SIZE 131 
#define  CFB32_BLOCK_SIZE 130 
#define  CFB64_BLOCK_SIZE 129 
#define  CFB8_BLOCK_SIZE 128 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 int atmel_aes_dma_transfer_start (struct atmel_aes_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_aes_dma_transfer_stop (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int atmel_aes_map (struct atmel_aes_dev*,struct scatterlist*,struct scatterlist*,size_t) ; 
 int /*<<< orphan*/  atmel_aes_unmap (struct atmel_aes_dev*) ; 

__attribute__((used)) static int atmel_aes_dma_start(struct atmel_aes_dev *dd,
			       struct scatterlist *src,
			       struct scatterlist *dst,
			       size_t len,
			       atmel_aes_fn_t resume)
{
	enum dma_slave_buswidth addr_width;
	u32 maxburst;
	int err;

	switch (dd->ctx->block_size) {
	case CFB8_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		maxburst = 1;
		break;

	case CFB16_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		maxburst = 1;
		break;

	case CFB32_BLOCK_SIZE:
	case CFB64_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		maxburst = 1;
		break;

	case AES_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		maxburst = dd->caps.max_burst_size;
		break;

	default:
		err = -EINVAL;
		goto exit;
	}

	err = atmel_aes_map(dd, src, dst, len);
	if (err)
		goto exit;

	dd->resume = resume;

	/* Set output DMA transfer first */
	err = atmel_aes_dma_transfer_start(dd, addr_width, DMA_DEV_TO_MEM,
					   maxburst);
	if (err)
		goto unmap;

	/* Then set input DMA transfer */
	err = atmel_aes_dma_transfer_start(dd, addr_width, DMA_MEM_TO_DEV,
					   maxburst);
	if (err)
		goto output_transfer_stop;

	return -EINPROGRESS;

output_transfer_stop:
	atmel_aes_dma_transfer_stop(dd, DMA_DEV_TO_MEM);
unmap:
	atmel_aes_unmap(dd);
exit:
	return atmel_aes_complete(dd, err);
}