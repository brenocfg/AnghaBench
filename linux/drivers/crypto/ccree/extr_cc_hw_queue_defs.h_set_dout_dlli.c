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
typedef  int /*<<< orphan*/  u32 ;
struct cc_hw_desc {int /*<<< orphan*/ * word; } ;
typedef  enum cc_axi_sec { ____Placeholder_cc_axi_sec } cc_axi_sec ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORD3_DOUT_LAST_IND ; 
 int /*<<< orphan*/  set_dout_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void set_dout_dlli(struct cc_hw_desc *pdesc, dma_addr_t addr,
				 u32 size, enum cc_axi_sec axi_sec,
				 u32 last_ind)
{
	set_dout_type(pdesc, DMA_DLLI, addr, size, axi_sec);
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_LAST_IND, last_ind);
}