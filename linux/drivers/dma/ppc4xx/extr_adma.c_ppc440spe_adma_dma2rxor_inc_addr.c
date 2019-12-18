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
struct ppc440spe_rxor {scalar_t__ addr_count; int /*<<< orphan*/  desc_count; } ;
struct ppc440spe_adma_desc_slot {int dummy; } ;

/* Variables and functions */
 scalar_t__ XOR_MAX_OPS ; 
 int /*<<< orphan*/  ppc440spe_desc_set_xor_src_cnt (struct ppc440spe_adma_desc_slot*,scalar_t__) ; 

__attribute__((used)) static void ppc440spe_adma_dma2rxor_inc_addr(
		struct ppc440spe_adma_desc_slot *desc,
		struct ppc440spe_rxor *cursor, int index, int src_cnt)
{
	cursor->addr_count++;
	if (index == src_cnt - 1) {
		ppc440spe_desc_set_xor_src_cnt(desc, cursor->addr_count);
	} else if (cursor->addr_count == XOR_MAX_OPS) {
		ppc440spe_desc_set_xor_src_cnt(desc, cursor->addr_count);
		cursor->addr_count = 0;
		cursor->desc_count++;
	}
}