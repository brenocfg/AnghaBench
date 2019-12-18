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
struct drmem_lmb {int flags; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  nid; int /*<<< orphan*/  drc_index; } ;

/* Variables and functions */
 int DRCONF_MEM_ASSIGNED ; 
 int EINVAL ; 
 int __add_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __remove_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int dlpar_online_lmb (struct drmem_lmb*) ; 
 int /*<<< orphan*/  dlpar_release_drc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_lmb_associativity_index (struct drmem_lmb*) ; 
 int /*<<< orphan*/  lmb_clear_nid (struct drmem_lmb*) ; 
 int /*<<< orphan*/  lmb_set_nid (struct drmem_lmb*) ; 
 unsigned long memory_block_size_bytes () ; 
 int update_lmb_associativity_index (struct drmem_lmb*) ; 

__attribute__((used)) static int dlpar_add_lmb(struct drmem_lmb *lmb)
{
	unsigned long block_sz;
	int rc;

	if (lmb->flags & DRCONF_MEM_ASSIGNED)
		return -EINVAL;

	rc = update_lmb_associativity_index(lmb);
	if (rc) {
		dlpar_release_drc(lmb->drc_index);
		return rc;
	}

	lmb_set_nid(lmb);
	block_sz = memory_block_size_bytes();

	/* Add the memory */
	rc = __add_memory(lmb->nid, lmb->base_addr, block_sz);
	if (rc) {
		invalidate_lmb_associativity_index(lmb);
		return rc;
	}

	rc = dlpar_online_lmb(lmb);
	if (rc) {
		__remove_memory(lmb->nid, lmb->base_addr, block_sz);
		invalidate_lmb_associativity_index(lmb);
		lmb_clear_nid(lmb);
	} else {
		lmb->flags |= DRCONF_MEM_ASSIGNED;
	}

	return rc;
}