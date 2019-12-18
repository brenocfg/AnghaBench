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
struct xor_cb {int cbc; } ;
struct ppc440spe_adma_desc_slot {struct xor_cb* hw_desc; } ;

/* Variables and functions */
 int XOR_CDCR_OAC_MSK ; 

__attribute__((used)) static inline void ppc440spe_desc_set_xor_src_cnt(
			struct ppc440spe_adma_desc_slot *desc,
			int src_cnt)
{
	struct xor_cb *hw_desc = desc->hw_desc;

	hw_desc->cbc &= ~XOR_CDCR_OAC_MSK;
	hw_desc->cbc |= src_cnt;
}