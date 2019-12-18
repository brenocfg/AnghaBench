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
struct TYPE_2__ {int max_xor; int max_pq; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  device_prep_dma_interrupt; int /*<<< orphan*/  device_prep_dma_xor_val; int /*<<< orphan*/  device_prep_dma_pq_val; int /*<<< orphan*/  device_prep_dma_pq; int /*<<< orphan*/  device_prep_dma_xor; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; } ;
struct ppc440spe_adma_device {int id; TYPE_1__ common; int /*<<< orphan*/  dev; } ;
struct dma_cdb {int dummy; } ;

/* Variables and functions */
 int DMA0_FIFO_SIZE ; 
 int DMA1_FIFO_SIZE ; 
 int /*<<< orphan*/  DMA_INTERRUPT ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_PQ_VAL ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int /*<<< orphan*/  DMA_XOR_VAL ; 
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int XOR_MAX_OPS ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_maxpq (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc440spe_adma_alloc_chan_resources ; 
 int /*<<< orphan*/  ppc440spe_adma_free_chan_resources ; 
 int /*<<< orphan*/  ppc440spe_adma_issue_pending ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_interrupt ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_memcpy ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_pq ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_pqzero_sum ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_xor ; 
 int /*<<< orphan*/  ppc440spe_adma_prep_dma_xor_zero_sum ; 
 int /*<<< orphan*/  ppc440spe_adma_tx_status ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void ppc440spe_adma_init_capabilities(struct ppc440spe_adma_device *adev)
{
	switch (adev->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		dma_cap_set(DMA_MEMCPY, adev->common.cap_mask);
		dma_cap_set(DMA_INTERRUPT, adev->common.cap_mask);
		dma_cap_set(DMA_PQ, adev->common.cap_mask);
		dma_cap_set(DMA_PQ_VAL, adev->common.cap_mask);
		dma_cap_set(DMA_XOR_VAL, adev->common.cap_mask);
		break;
	case PPC440SPE_XOR_ID:
		dma_cap_set(DMA_XOR, adev->common.cap_mask);
		dma_cap_set(DMA_PQ, adev->common.cap_mask);
		dma_cap_set(DMA_INTERRUPT, adev->common.cap_mask);
		adev->common.cap_mask = adev->common.cap_mask;
		break;
	}

	/* Set base routines */
	adev->common.device_alloc_chan_resources =
				ppc440spe_adma_alloc_chan_resources;
	adev->common.device_free_chan_resources =
				ppc440spe_adma_free_chan_resources;
	adev->common.device_tx_status = ppc440spe_adma_tx_status;
	adev->common.device_issue_pending = ppc440spe_adma_issue_pending;

	/* Set prep routines based on capability */
	if (dma_has_cap(DMA_MEMCPY, adev->common.cap_mask)) {
		adev->common.device_prep_dma_memcpy =
			ppc440spe_adma_prep_dma_memcpy;
	}
	if (dma_has_cap(DMA_XOR, adev->common.cap_mask)) {
		adev->common.max_xor = XOR_MAX_OPS;
		adev->common.device_prep_dma_xor =
			ppc440spe_adma_prep_dma_xor;
	}
	if (dma_has_cap(DMA_PQ, adev->common.cap_mask)) {
		switch (adev->id) {
		case PPC440SPE_DMA0_ID:
			dma_set_maxpq(&adev->common,
				DMA0_FIFO_SIZE / sizeof(struct dma_cdb), 0);
			break;
		case PPC440SPE_DMA1_ID:
			dma_set_maxpq(&adev->common,
				DMA1_FIFO_SIZE / sizeof(struct dma_cdb), 0);
			break;
		case PPC440SPE_XOR_ID:
			adev->common.max_pq = XOR_MAX_OPS * 3;
			break;
		}
		adev->common.device_prep_dma_pq =
			ppc440spe_adma_prep_dma_pq;
	}
	if (dma_has_cap(DMA_PQ_VAL, adev->common.cap_mask)) {
		switch (adev->id) {
		case PPC440SPE_DMA0_ID:
			adev->common.max_pq = DMA0_FIFO_SIZE /
						sizeof(struct dma_cdb);
			break;
		case PPC440SPE_DMA1_ID:
			adev->common.max_pq = DMA1_FIFO_SIZE /
						sizeof(struct dma_cdb);
			break;
		}
		adev->common.device_prep_dma_pq_val =
			ppc440spe_adma_prep_dma_pqzero_sum;
	}
	if (dma_has_cap(DMA_XOR_VAL, adev->common.cap_mask)) {
		switch (adev->id) {
		case PPC440SPE_DMA0_ID:
			adev->common.max_xor = DMA0_FIFO_SIZE /
						sizeof(struct dma_cdb);
			break;
		case PPC440SPE_DMA1_ID:
			adev->common.max_xor = DMA1_FIFO_SIZE /
						sizeof(struct dma_cdb);
			break;
		}
		adev->common.device_prep_dma_xor_val =
			ppc440spe_adma_prep_dma_xor_zero_sum;
	}
	if (dma_has_cap(DMA_INTERRUPT, adev->common.cap_mask)) {
		adev->common.device_prep_dma_interrupt =
			ppc440spe_adma_prep_dma_interrupt;
	}
	pr_info("%s: AMCC(R) PPC440SP(E) ADMA Engine: "
	  "( %s%s%s%s%s%s)\n",
	  dev_name(adev->dev),
	  dma_has_cap(DMA_PQ, adev->common.cap_mask) ? "pq " : "",
	  dma_has_cap(DMA_PQ_VAL, adev->common.cap_mask) ? "pq_val " : "",
	  dma_has_cap(DMA_XOR, adev->common.cap_mask) ? "xor " : "",
	  dma_has_cap(DMA_XOR_VAL, adev->common.cap_mask) ? "xor_val " : "",
	  dma_has_cap(DMA_MEMCPY, adev->common.cap_mask) ? "memcpy " : "",
	  dma_has_cap(DMA_INTERRUPT, adev->common.cap_mask) ? "intr " : "");
}