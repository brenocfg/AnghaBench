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
typedef  int u64 ;
typedef  int u32 ;
struct xilly_endpoint {int msgbuf_dma_addr; int msg_buf_size; scalar_t__ registers; void* msgbuf_addr; TYPE_1__* ephw; struct device* dev; } ;
struct xilly_buffer {int dma_addr; void* addr; } ;
struct xilly_alloc_state {int left_of_salami; int regdirection; void* salami; int /*<<< orphan*/  nbuffer; int /*<<< orphan*/  direction; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int (* map_single ) (struct xilly_endpoint*,void*,int,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_DMA32 ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ devm_get_free_pages (struct device*,int,int) ; 
 struct xilly_buffer* devm_kcalloc (struct device*,int,int,int) ; 
 scalar_t__ fpga_dma_bufaddr_highaddr_reg ; 
 scalar_t__ fpga_dma_bufaddr_lowaddr_reg ; 
 scalar_t__ fpga_dma_bufno_reg ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int stub1 (struct xilly_endpoint*,void*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int xilly_get_dma_buffers(struct xilly_endpoint *ep,
				 struct xilly_alloc_state *s,
				 struct xilly_buffer **buffers,
				 int bufnum, int bytebufsize)
{
	int i, rc;
	dma_addr_t dma_addr;
	struct device *dev = ep->dev;
	struct xilly_buffer *this_buffer = NULL; /* Init to silence warning */

	if (buffers) { /* Not the message buffer */
		this_buffer = devm_kcalloc(dev, bufnum,
					   sizeof(struct xilly_buffer),
					   GFP_KERNEL);
		if (!this_buffer)
			return -ENOMEM;
	}

	for (i = 0; i < bufnum; i++) {
		/*
		 * Buffers are expected in descending size order, so there
		 * is either enough space for this buffer or none at all.
		 */

		if ((s->left_of_salami < bytebufsize) &&
		    (s->left_of_salami > 0)) {
			dev_err(ep->dev,
				"Corrupt buffer allocation in IDT. Aborting.\n");
			return -ENODEV;
		}

		if (s->left_of_salami == 0) {
			int allocorder, allocsize;

			allocsize = PAGE_SIZE;
			allocorder = 0;
			while (bytebufsize > allocsize) {
				allocsize *= 2;
				allocorder++;
			}

			s->salami = (void *) devm_get_free_pages(
				dev,
				GFP_KERNEL | __GFP_DMA32 | __GFP_ZERO,
				allocorder);
			if (!s->salami)
				return -ENOMEM;

			s->left_of_salami = allocsize;
		}

		rc = ep->ephw->map_single(ep, s->salami,
					  bytebufsize, s->direction,
					  &dma_addr);
		if (rc)
			return rc;

		iowrite32((u32) (dma_addr & 0xffffffff),
			  ep->registers + fpga_dma_bufaddr_lowaddr_reg);
		iowrite32(((u32) ((((u64) dma_addr) >> 32) & 0xffffffff)),
			  ep->registers + fpga_dma_bufaddr_highaddr_reg);

		if (buffers) { /* Not the message buffer */
			this_buffer->addr = s->salami;
			this_buffer->dma_addr = dma_addr;
			buffers[i] = this_buffer++;

			iowrite32(s->regdirection | s->nbuffer++,
				  ep->registers + fpga_dma_bufno_reg);
		} else {
			ep->msgbuf_addr = s->salami;
			ep->msgbuf_dma_addr = dma_addr;
			ep->msg_buf_size = bytebufsize;

			iowrite32(s->regdirection,
				  ep->registers + fpga_dma_bufno_reg);
		}

		s->left_of_salami -= bytebufsize;
		s->salami += bytebufsize;
	}
	return 0;
}