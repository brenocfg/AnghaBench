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
typedef  int u16 ;
struct cc_hw_desc {int* word; } ;
typedef  enum cc_dma_mode { ____Placeholder_cc_dma_mode } cc_dma_mode ;
typedef  enum cc_axi_sec { ____Placeholder_cc_axi_sec } cc_axi_sec ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD1_DIN_DMA_MODE ; 
 int /*<<< orphan*/  WORD1_DIN_SIZE ; 
 int /*<<< orphan*/  WORD1_NS_BIT ; 
 int /*<<< orphan*/  WORD5_DIN_ADDR_HIGH ; 

__attribute__((used)) static inline void set_din_type(struct cc_hw_desc *pdesc,
				enum cc_dma_mode dma_mode, dma_addr_t addr,
				u32 size, enum cc_axi_sec axi_sec)
{
	pdesc->word[0] = (u32)addr;
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	pdesc->word[5] |= FIELD_PREP(WORD5_DIN_ADDR_HIGH, ((u16)(addr >> 32)));
#endif
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_DMA_MODE, dma_mode) |
				FIELD_PREP(WORD1_DIN_SIZE, size) |
				FIELD_PREP(WORD1_NS_BIT, axi_sec);
}