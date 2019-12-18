#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ zb_level; int /*<<< orphan*/  zb_blkid; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
struct TYPE_9__ {int /*<<< orphan*/  dn_indblkshift; int /*<<< orphan*/  dn_datablkszsec; } ;
typedef  TYPE_2__ dnode_phys_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 unsigned long long DNODE_BLOCK_SHIFT ; 
 unsigned long long SPA_MINBLOCKSHIFT ; 
 scalar_t__ zbookmark_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__ const*) ; 

boolean_t
zbookmark_subtree_completed(const dnode_phys_t *dnp,
    const zbookmark_phys_t *subtree_root, const zbookmark_phys_t *last_block)
{
	zbookmark_phys_t mod_zb = *subtree_root;
	mod_zb.zb_blkid++;
	ASSERT(last_block->zb_level == 0);

	/* The objset_phys_t isn't before anything. */
	if (dnp == NULL)
		return (B_FALSE);

	/*
	 * We pass in 1ULL << (DNODE_BLOCK_SHIFT - SPA_MINBLOCKSHIFT) for the
	 * data block size in sectors, because that variable is only used if
	 * the bookmark refers to a block in the meta-dnode.  Since we don't
	 * know without examining it what object it refers to, and there's no
	 * harm in passing in this value in other cases, we always pass it in.
	 *
	 * We pass in 0 for the indirect block size shift because zb2 must be
	 * level 0.  The indirect block size is only used to calculate the span
	 * of the bookmark, but since the bookmark must be level 0, the span is
	 * always 1, so the math works out.
	 *
	 * If you make changes to how the zbookmark_compare code works, be sure
	 * to make sure that this code still works afterwards.
	 */
	return (zbookmark_compare(dnp->dn_datablkszsec, dnp->dn_indblkshift,
	    1ULL << (DNODE_BLOCK_SHIFT - SPA_MINBLOCKSHIFT), 0, &mod_zb,
	    last_block) <= 0);
}