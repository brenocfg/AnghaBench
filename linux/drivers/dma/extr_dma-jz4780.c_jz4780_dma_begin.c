#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ callback; } ;
struct virt_dma_desc {TYPE_1__ tx; int /*<<< orphan*/  node; } ;
struct jz4780_dma_dev {int dummy; } ;
struct jz4780_dma_chan {int curr_hwdesc; int /*<<< orphan*/  id; TYPE_3__* desc; scalar_t__ transfer_type; int /*<<< orphan*/  vchan; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {scalar_t__ type; unsigned int count; scalar_t__ desc_phys; TYPE_2__* desc; } ;
struct TYPE_5__ {scalar_t__ dtc; int /*<<< orphan*/  dcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_CYCLIC ; 
 int /*<<< orphan*/  JZ_DMA_DCM_LINK ; 
 scalar_t__ JZ_DMA_DCS_CTE ; 
 int /*<<< orphan*/  JZ_DMA_REG_DCS ; 
 int /*<<< orphan*/  JZ_DMA_REG_DDA ; 
 int /*<<< orphan*/  JZ_DMA_REG_DDRS ; 
 int /*<<< orphan*/  JZ_DMA_REG_DRT ; 
 int /*<<< orphan*/  JZ_DMA_REG_DTC ; 
 int /*<<< orphan*/  jz4780_dma_chan_enable (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 
 struct jz4780_dma_dev* jz4780_dma_chan_parent (struct jz4780_dma_chan*) ; 
 int /*<<< orphan*/  jz4780_dma_chn_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jz4780_dma_ctrl_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_3__* to_jz4780_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jz4780_dma_begin(struct jz4780_dma_chan *jzchan)
{
	struct jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	struct virt_dma_desc *vdesc;
	unsigned int i;
	dma_addr_t desc_phys;

	if (!jzchan->desc) {
		vdesc = vchan_next_desc(&jzchan->vchan);
		if (!vdesc)
			return;

		list_del(&vdesc->node);

		jzchan->desc = to_jz4780_dma_desc(vdesc);
		jzchan->curr_hwdesc = 0;

		if (jzchan->desc->type == DMA_CYCLIC && vdesc->tx.callback) {
			/*
			 * The DMA controller doesn't support triggering an
			 * interrupt after processing each descriptor, only
			 * after processing an entire terminated list of
			 * descriptors. For a cyclic DMA setup the list of
			 * descriptors is not terminated so we can never get an
			 * interrupt.
			 *
			 * If the user requested a callback for a cyclic DMA
			 * setup then we workaround this hardware limitation
			 * here by degrading to a set of unlinked descriptors
			 * which we will submit in sequence in response to the
			 * completion of processing the previous descriptor.
			 */
			for (i = 0; i < jzchan->desc->count; i++)
				jzchan->desc->desc[i].dcm &= ~JZ_DMA_DCM_LINK;
		}
	} else {
		/*
		 * There is an existing transfer, therefore this must be one
		 * for which we unlinked the descriptors above. Advance to the
		 * next one in the list.
		 */
		jzchan->curr_hwdesc =
			(jzchan->curr_hwdesc + 1) % jzchan->desc->count;
	}

	/* Enable the channel's clock. */
	jz4780_dma_chan_enable(jzdma, jzchan->id);

	/* Use 4-word descriptors. */
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DCS, 0);

	/* Set transfer type. */
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DRT,
			      jzchan->transfer_type);

	/*
	 * Set the transfer count. This is redundant for a descriptor-driven
	 * transfer. However, there can be a delay between the transfer start
	 * time and when DTCn reg contains the new transfer count. Setting
	 * it explicitly ensures residue is computed correctly at all times.
	 */
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DTC,
				jzchan->desc->desc[jzchan->curr_hwdesc].dtc);

	/* Write descriptor address and initiate descriptor fetch. */
	desc_phys = jzchan->desc->desc_phys +
		    (jzchan->curr_hwdesc * sizeof(*jzchan->desc->desc));
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DDA, desc_phys);
	jz4780_dma_ctrl_writel(jzdma, JZ_DMA_REG_DDRS, BIT(jzchan->id));

	/* Enable the channel. */
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DCS,
			      JZ_DMA_DCS_CTE);
}