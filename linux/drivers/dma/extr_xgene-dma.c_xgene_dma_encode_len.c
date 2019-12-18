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
typedef  int u64 ;

/* Variables and functions */
 int XGENE_DMA_16K_BUFFER_LEN_CODE ; 
 int XGENE_DMA_DESC_BUFLEN_POS ; 
 size_t XGENE_DMA_MAX_BYTE_CNT ; 

__attribute__((used)) static u64 xgene_dma_encode_len(size_t len)
{
	return (len < XGENE_DMA_MAX_BYTE_CNT) ?
		((u64)len << XGENE_DMA_DESC_BUFLEN_POS) :
		XGENE_DMA_16K_BUFFER_LEN_CODE;
}