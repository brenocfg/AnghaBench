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
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD3_DOUT_LAST_IND ; 
 int /*<<< orphan*/  WORD3_DOUT_SIZE ; 

__attribute__((used)) static inline void set_dout_no_dma(struct cc_hw_desc *pdesc, u32 addr,
				   u32 size, bool write_enable)
{
	pdesc->word[2] = addr;
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_SIZE, size) |
			FIELD_PREP(WORD3_DOUT_LAST_IND, write_enable);
}