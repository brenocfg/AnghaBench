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
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct ppc440spe_adma_desc_slot {int dst_cnt; struct ppc440spe_adma_desc_slot* group_head; TYPE_1__ async_tx; } ;
struct ppc440spe_adma_chan {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int /*<<< orphan*/  ppc440spe_desc_set_dest_addr (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ppc440spe_adma_desc_slot* ppc440spe_get_group_entry (struct ppc440spe_adma_desc_slot*,int) ; 
 struct ppc440spe_adma_chan* to_ppc440spe_adma_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppc440spe_adma_set_dest(struct ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t addr, int index)
{
	struct ppc440spe_adma_chan *chan;

	BUG_ON(index >= sw_desc->dst_cnt);

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		/* to do: support transfers lengths >
		 * PPC440SPE_ADMA_DMA/XOR_MAX_BYTE_COUNT
		 */
		ppc440spe_desc_set_dest_addr(sw_desc->group_head,
			chan, 0, addr, index);
		break;
	case PPC440SPE_XOR_ID:
		sw_desc = ppc440spe_get_group_entry(sw_desc, index);
		ppc440spe_desc_set_dest_addr(sw_desc,
			chan, 0, addr, index);
		break;
	}
}