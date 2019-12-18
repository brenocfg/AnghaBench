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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_POE_CLASS_SETUP_CFG ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_setup_poe_class_config(uint64_t nae_base, int max_poe_classes,
    int num_contexts, int *poe_cl_tbl)
{
	uint32_t val;
	int i, max_poe_class_ctxt_tbl_sz;

	max_poe_class_ctxt_tbl_sz = num_contexts/max_poe_classes;
	for (i = 0; i < max_poe_class_ctxt_tbl_sz; i++) {
		val = (poe_cl_tbl[(i/max_poe_classes) & 0x7] << 8) | i;
		nlm_write_nae_reg(nae_base, NAE_POE_CLASS_SETUP_CFG, val);
	}
}