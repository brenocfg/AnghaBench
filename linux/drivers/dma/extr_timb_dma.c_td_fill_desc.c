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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct timb_dma_chan {int /*<<< orphan*/  chan; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int*,unsigned long long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static int td_fill_desc(struct timb_dma_chan *td_chan, u8 *dma_desc,
	struct scatterlist *sg, bool last)
{
	if (sg_dma_len(sg) > USHRT_MAX) {
		dev_err(chan2dev(&td_chan->chan), "Too big sg element\n");
		return -EINVAL;
	}

	/* length must be word aligned */
	if (sg_dma_len(sg) % sizeof(u32)) {
		dev_err(chan2dev(&td_chan->chan), "Incorrect length: %d\n",
			sg_dma_len(sg));
		return -EINVAL;
	}

	dev_dbg(chan2dev(&td_chan->chan), "desc: %p, addr: 0x%llx\n",
		dma_desc, (unsigned long long)sg_dma_address(sg));

	dma_desc[7] = (sg_dma_address(sg) >> 24) & 0xff;
	dma_desc[6] = (sg_dma_address(sg) >> 16) & 0xff;
	dma_desc[5] = (sg_dma_address(sg) >> 8) & 0xff;
	dma_desc[4] = (sg_dma_address(sg) >> 0) & 0xff;

	dma_desc[3] = (sg_dma_len(sg) >> 8) & 0xff;
	dma_desc[2] = (sg_dma_len(sg) >> 0) & 0xff;

	dma_desc[1] = 0x00;
	dma_desc[0] = 0x21 | (last ? 0x02 : 0); /* tran, valid */

	return 0;
}