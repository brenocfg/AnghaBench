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
typedef  int /*<<< orphan*/  u8 ;
struct ppc440spe_adma_desc_slot {struct dma_cdb* hw_desc; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct dma_cdb {int /*<<< orphan*/  sg2u; int /*<<< orphan*/  sg2l; int /*<<< orphan*/  sg3u; int /*<<< orphan*/  sg3l; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PPC440SPE_DMA0_ID 129 
#define  PPC440SPE_DMA1_ID 128 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppc440spe_desc_set_dcheck(struct ppc440spe_adma_desc_slot *desc,
				struct ppc440spe_adma_chan *chan, u8 *qword)
{
	struct dma_cdb *dma_hw_desc;

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		dma_hw_desc = desc->hw_desc;
		iowrite32(qword[0], &dma_hw_desc->sg3l);
		iowrite32(qword[4], &dma_hw_desc->sg3u);
		iowrite32(qword[8], &dma_hw_desc->sg2l);
		iowrite32(qword[12], &dma_hw_desc->sg2u);
		break;
	default:
		BUG();
	}
}