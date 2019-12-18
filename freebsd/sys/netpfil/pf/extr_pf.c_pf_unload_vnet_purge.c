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

/* Variables and functions */
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  pf_hashmask ; 
 int /*<<< orphan*/  pf_purge_expired_src_nodes () ; 
 int /*<<< orphan*/  pf_purge_expired_states (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_purge_fragments (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_purge_unlinked_rules () ; 
 int /*<<< orphan*/  pfi_kif_purge () ; 

void
pf_unload_vnet_purge(void)
{

	/*
	 * To cleanse up all kifs and rules we need
	 * two runs: first one clears reference flags,
	 * then pf_purge_expired_states() doesn't
	 * raise them, and then second run frees.
	 */
	pf_purge_unlinked_rules();
	pfi_kif_purge();

	/*
	 * Now purge everything.
	 */
	pf_purge_expired_states(0, pf_hashmask);
	pf_purge_fragments(UINT_MAX);
	pf_purge_expired_src_nodes();

	/*
	 * Now all kifs & rules should be unreferenced,
	 * thus should be successfully freed.
	 */
	pf_purge_unlinked_rules();
	pfi_kif_purge();
}