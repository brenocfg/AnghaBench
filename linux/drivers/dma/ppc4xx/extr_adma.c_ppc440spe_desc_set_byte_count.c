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
typedef  int /*<<< orphan*/  u32 ;
struct xor_cb {int /*<<< orphan*/  cbbc; int /*<<< orphan*/  cnt; } ;
struct ppc440spe_adma_desc_slot {struct xor_cb* hw_desc; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct dma_cdb {int /*<<< orphan*/  cbbc; int /*<<< orphan*/  cnt; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppc440spe_desc_set_byte_count(struct ppc440spe_adma_desc_slot *desc,
				struct ppc440spe_adma_chan *chan,
				u32 byte_count)
{
	struct dma_cdb *dma_hw_desc;
	struct xor_cb *xor_hw_desc;

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		dma_hw_desc = desc->hw_desc;
		dma_hw_desc->cnt = cpu_to_le32(byte_count);
		break;
	case PPC440SPE_XOR_ID:
		xor_hw_desc = desc->hw_desc;
		xor_hw_desc->cbbc = byte_count;
		break;
	}
}