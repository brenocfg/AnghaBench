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
typedef  size_t dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 size_t XGENE_DMA_MAX_BYTE_CNT ; 
 int /*<<< orphan*/  cpu_to_le64 (size_t) ; 
 size_t xgene_dma_encode_len (size_t) ; 

__attribute__((used)) static void xgene_dma_set_src_buffer(__le64 *ext8, size_t *len,
				     dma_addr_t *paddr)
{
	size_t nbytes = (*len < XGENE_DMA_MAX_BYTE_CNT) ?
			*len : XGENE_DMA_MAX_BYTE_CNT;

	*ext8 |= cpu_to_le64(*paddr);
	*ext8 |= cpu_to_le64(xgene_dma_encode_len(nbytes));
	*len -= nbytes;
	*paddr += nbytes;
}