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
struct cc_hw_desc {int* word; } ;

/* Variables and functions */
 int DMA_SRAM ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD1_DIN_CONST_VALUE ; 
 int /*<<< orphan*/  WORD1_DIN_DMA_MODE ; 
 int /*<<< orphan*/  WORD1_DIN_SIZE ; 

__attribute__((used)) static inline void set_din_const(struct cc_hw_desc *pdesc, u32 val, u32 size)
{
	pdesc->word[0] = val;
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_CONST_VALUE, 1) |
			FIELD_PREP(WORD1_DIN_DMA_MODE, DMA_SRAM) |
			FIELD_PREP(WORD1_DIN_SIZE, size);
}