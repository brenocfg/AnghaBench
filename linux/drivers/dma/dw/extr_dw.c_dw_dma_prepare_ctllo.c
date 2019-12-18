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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  m_master; int /*<<< orphan*/  p_master; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; } ;
struct dw_dma_chan {scalar_t__ direction; TYPE_1__ dws; struct dma_slave_config dma_sconfig; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int DWC_CTLL_DMS (int /*<<< orphan*/ ) ; 
 int DWC_CTLL_DST_MSIZE (int /*<<< orphan*/ ) ; 
 int DWC_CTLL_LLP_D_EN ; 
 int DWC_CTLL_LLP_S_EN ; 
 int DWC_CTLL_SMS (int /*<<< orphan*/ ) ; 
 int DWC_CTLL_SRC_MSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DMA_MSIZE_16 ; 
 int is_slave_direction (scalar_t__) ; 

__attribute__((used)) static u32 dw_dma_prepare_ctllo(struct dw_dma_chan *dwc)
{
	struct dma_slave_config	*sconfig = &dwc->dma_sconfig;
	bool is_slave = is_slave_direction(dwc->direction);
	u8 smsize = is_slave ? sconfig->src_maxburst : DW_DMA_MSIZE_16;
	u8 dmsize = is_slave ? sconfig->dst_maxburst : DW_DMA_MSIZE_16;
	u8 p_master = dwc->dws.p_master;
	u8 m_master = dwc->dws.m_master;
	u8 dms = (dwc->direction == DMA_MEM_TO_DEV) ? p_master : m_master;
	u8 sms = (dwc->direction == DMA_DEV_TO_MEM) ? p_master : m_master;

	return DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN |
	       DWC_CTLL_DST_MSIZE(dmsize) | DWC_CTLL_SRC_MSIZE(smsize) |
	       DWC_CTLL_DMS(dms) | DWC_CTLL_SMS(sms);
}