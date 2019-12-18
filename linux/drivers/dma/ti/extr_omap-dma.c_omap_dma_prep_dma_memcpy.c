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
typedef  scalar_t__ uint8_t ;
struct omap_desc {size_t dev_addr; int sglen; int ccr; int cicr; int polled; int csdp; int /*<<< orphan*/  vd; TYPE_1__* sg; scalar_t__ es; scalar_t__ fi; int /*<<< orphan*/  dir; } ;
struct omap_chan {int ccr; int /*<<< orphan*/  vc; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {size_t en; int fn; size_t addr; } ;

/* Variables and functions */
 size_t BIT (scalar_t__) ; 
 int CCR_DST_AMODE_POSTINC ; 
 int CCR_SRC_AMODE_POSTINC ; 
 int CICR_FRAME_IE ; 
 int CICR_MISALIGNED_ERR_IE ; 
 int CICR_TOUT_IE ; 
 int CICR_TRANS_ERR_IE ; 
 scalar_t__ CSDP_DATA_TYPE_32 ; 
 int CSDP_DST_BURST_64 ; 
 int CSDP_DST_PACKED ; 
 int CSDP_DST_PORT_EMIFF ; 
 int CSDP_SRC_BURST_64 ; 
 int CSDP_SRC_PACKED ; 
 int CSDP_SRC_PORT_EMIFF ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ __ffs (size_t) ; 
 scalar_t__ dma_omap1 () ; 
 struct omap_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct omap_chan* to_omap_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *omap_dma_prep_dma_memcpy(
	struct dma_chan *chan, dma_addr_t dest, dma_addr_t src,
	size_t len, unsigned long tx_flags)
{
	struct omap_chan *c = to_omap_dma_chan(chan);
	struct omap_desc *d;
	uint8_t data_type;

	d = kzalloc(sizeof(*d) + sizeof(d->sg[0]), GFP_ATOMIC);
	if (!d)
		return NULL;

	data_type = __ffs((src | dest | len));
	if (data_type > CSDP_DATA_TYPE_32)
		data_type = CSDP_DATA_TYPE_32;

	d->dir = DMA_MEM_TO_MEM;
	d->dev_addr = src;
	d->fi = 0;
	d->es = data_type;
	d->sg[0].en = len / BIT(data_type);
	d->sg[0].fn = 1;
	d->sg[0].addr = dest;
	d->sglen = 1;
	d->ccr = c->ccr;
	d->ccr |= CCR_DST_AMODE_POSTINC | CCR_SRC_AMODE_POSTINC;

	if (tx_flags & DMA_PREP_INTERRUPT)
		d->cicr |= CICR_FRAME_IE;
	else
		d->polled = true;

	d->csdp = data_type;

	if (dma_omap1()) {
		d->cicr |= CICR_TOUT_IE;
		d->csdp |= CSDP_DST_PORT_EMIFF | CSDP_SRC_PORT_EMIFF;
	} else {
		d->csdp |= CSDP_DST_PACKED | CSDP_SRC_PACKED;
		d->cicr |= CICR_MISALIGNED_ERR_IE | CICR_TRANS_ERR_IE;
		d->csdp |= CSDP_DST_BURST_64 | CSDP_SRC_BURST_64;
	}

	return vchan_tx_prep(&c->vc, &d->vd, tx_flags);
}