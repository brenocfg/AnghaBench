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
typedef  int u32 ;
struct owl_dma_vchan {int /*<<< orphan*/  drq; } ;
struct owl_dma_lli_hw {int fcnt; int flen; void* ctrlb; int /*<<< orphan*/  ctrla; scalar_t__ dst_stride; scalar_t__ src_stride; void* daddr; void* saddr; scalar_t__ next_lli; } ;
struct owl_dma_lli {struct owl_dma_lli_hw hw; } ;
struct dma_slave_config {int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr_width; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 130 
#define  DMA_MEM_TO_DEV 129 
#define  DMA_MEM_TO_MEM 128 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int EINVAL ; 
 int /*<<< orphan*/  OWL_DMA_INTCTL_BLOCK ; 
 int /*<<< orphan*/  OWL_DMA_INTCTL_SUPER_BLOCK ; 
 int OWL_DMA_LLC_DAV_LOAD_NEXT ; 
 int OWL_DMA_LLC_SAV_LOAD_NEXT ; 
 int OWL_DMA_MODE_DAM_CONST ; 
 int OWL_DMA_MODE_DAM_INC ; 
 int OWL_DMA_MODE_DT_DCU ; 
 int OWL_DMA_MODE_DT_DEV ; 
 int OWL_DMA_MODE_NDDBW_8BIT ; 
 int OWL_DMA_MODE_PW (int /*<<< orphan*/ ) ; 
 int OWL_DMA_MODE_SAM_CONST ; 
 int OWL_DMA_MODE_SAM_INC ; 
 int OWL_DMA_MODE_ST_DCU ; 
 int OWL_DMA_MODE_ST_DEV ; 
 int OWL_DMA_MODE_TS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_hw_ctrla (int,int) ; 
 void* llc_hw_ctrlb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int owl_dma_cfg_lli(struct owl_dma_vchan *vchan,
				  struct owl_dma_lli *lli,
				  dma_addr_t src, dma_addr_t dst,
				  u32 len, enum dma_transfer_direction dir,
				  struct dma_slave_config *sconfig,
				  bool is_cyclic)
{
	struct owl_dma_lli_hw *hw = &lli->hw;
	u32 mode;

	mode = OWL_DMA_MODE_PW(0);

	switch (dir) {
	case DMA_MEM_TO_MEM:
		mode |= OWL_DMA_MODE_TS(0) | OWL_DMA_MODE_ST_DCU |
			OWL_DMA_MODE_DT_DCU | OWL_DMA_MODE_SAM_INC |
			OWL_DMA_MODE_DAM_INC;

		break;
	case DMA_MEM_TO_DEV:
		mode |= OWL_DMA_MODE_TS(vchan->drq)
			| OWL_DMA_MODE_ST_DCU | OWL_DMA_MODE_DT_DEV
			| OWL_DMA_MODE_SAM_INC | OWL_DMA_MODE_DAM_CONST;

		/*
		 * Hardware only supports 32bit and 8bit buswidth. Since the
		 * default is 32bit, select 8bit only when requested.
		 */
		if (sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_1_BYTE)
			mode |= OWL_DMA_MODE_NDDBW_8BIT;

		break;
	case DMA_DEV_TO_MEM:
		 mode |= OWL_DMA_MODE_TS(vchan->drq)
			| OWL_DMA_MODE_ST_DEV | OWL_DMA_MODE_DT_DCU
			| OWL_DMA_MODE_SAM_CONST | OWL_DMA_MODE_DAM_INC;

		/*
		 * Hardware only supports 32bit and 8bit buswidth. Since the
		 * default is 32bit, select 8bit only when requested.
		 */
		if (sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_1_BYTE)
			mode |= OWL_DMA_MODE_NDDBW_8BIT;

		break;
	default:
		return -EINVAL;
	}

	hw->next_lli = 0; /* One link list by default */
	hw->saddr = src;
	hw->daddr = dst;

	hw->fcnt = 1; /* Frame count fixed as 1 */
	hw->flen = len; /* Max frame length is 1MB */
	hw->src_stride = 0;
	hw->dst_stride = 0;
	hw->ctrla = llc_hw_ctrla(mode,
				 OWL_DMA_LLC_SAV_LOAD_NEXT |
				 OWL_DMA_LLC_DAV_LOAD_NEXT);

	if (is_cyclic)
		hw->ctrlb = llc_hw_ctrlb(OWL_DMA_INTCTL_BLOCK);
	else
		hw->ctrlb = llc_hw_ctrlb(OWL_DMA_INTCTL_SUPER_BLOCK);

	return 0;
}