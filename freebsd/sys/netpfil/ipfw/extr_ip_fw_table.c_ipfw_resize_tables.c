#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct table_info {int /*<<< orphan*/ * lookup; } ;
struct table_config {int /*<<< orphan*/  astate; TYPE_1__* ta; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {void* tablestate; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* change_ti ) (int /*<<< orphan*/ ,struct table_info*) ;} ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int EINVAL ; 
 unsigned int IPFW_TABLES_MAX ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 unsigned int V_fw_tables_max ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_alloc (unsigned int,void*,int*) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_free (void*,int) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_merge (struct namedobj_instance*,void**,int*) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_swap (struct namedobj_instance*,void**,int*) ; 
 scalar_t__ ipfw_objhash_lookup_kidx (struct namedobj_instance*,int) ; 
 void* malloc (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ roundup2p (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct table_info*) ; 

int
ipfw_resize_tables(struct ip_fw_chain *ch, unsigned int ntables)
{
	unsigned int ntables_old, tbl;
	struct namedobj_instance *ni;
	void *new_idx, *old_tablestate, *tablestate;
	struct table_info *ti;
	struct table_config *tc;
	int i, new_blocks;

	/* Check new value for validity */
	if (ntables == 0)
		return (EINVAL);
	if (ntables > IPFW_TABLES_MAX)
		ntables = IPFW_TABLES_MAX;
	/* Alight to nearest power of 2 */
	ntables = (unsigned int)roundup2p(ntables); 

	/* Allocate new pointers */
	tablestate = malloc(ntables * sizeof(struct table_info),
	    M_IPFW, M_WAITOK | M_ZERO);

	ipfw_objhash_bitmap_alloc(ntables, (void *)&new_idx, &new_blocks);

	IPFW_UH_WLOCK(ch);

	tbl = (ntables >= V_fw_tables_max) ? V_fw_tables_max : ntables;
	ni = CHAIN_TO_NI(ch);

	/* Temporary restrict decreasing max_tables */
	if (ntables < V_fw_tables_max) {

		/*
		 * FIXME: Check if we really can shrink
		 */
		IPFW_UH_WUNLOCK(ch);
		return (EINVAL);
	}

	/* Copy table info/indices */
	memcpy(tablestate, ch->tablestate, sizeof(struct table_info) * tbl);
	ipfw_objhash_bitmap_merge(ni, &new_idx, &new_blocks);

	IPFW_WLOCK(ch);

	/* Change pointers */
	old_tablestate = ch->tablestate;
	ch->tablestate = tablestate;
	ipfw_objhash_bitmap_swap(ni, &new_idx, &new_blocks);

	ntables_old = V_fw_tables_max;
	V_fw_tables_max = ntables;

	IPFW_WUNLOCK(ch);

	/* Notify all consumers that their @ti pointer has changed */
	ti = (struct table_info *)ch->tablestate;
	for (i = 0; i < tbl; i++, ti++) {
		if (ti->lookup == NULL)
			continue;
		tc = (struct table_config *)ipfw_objhash_lookup_kidx(ni, i);
		if (tc == NULL || tc->ta->change_ti == NULL)
			continue;

		tc->ta->change_ti(tc->astate, ti);
	}

	IPFW_UH_WUNLOCK(ch);

	/* Free old pointers */
	free(old_tablestate, M_IPFW);
	ipfw_objhash_bitmap_free(new_idx, new_blocks);

	return (0);
}