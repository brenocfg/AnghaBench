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
struct vdump_args {struct table_value* pval; } ;
struct tables_config {int val_size; } ;
struct table_value {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {struct table_value* valuestate; } ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 struct tables_config* CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 struct namedobj_instance* CHAIN_TO_VI (struct ip_fw_chain*) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct table_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_alloc (int,void*,int*) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_free (void*,int) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_merge (struct namedobj_instance*,void**,int*) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_swap (struct namedobj_instance*,void**,int*) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach (struct namedobj_instance*,int /*<<< orphan*/ ,struct vdump_args*) ; 
 struct table_value* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct table_value*,struct table_value*,int) ; 
 int /*<<< orphan*/  memset (struct vdump_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rollback_toperation_state (struct ip_fw_chain*,struct ip_fw_chain*) ; 
 int /*<<< orphan*/  update_tvalue ; 

__attribute__((used)) static int
resize_shared_value_storage(struct ip_fw_chain *ch)
{
	struct tables_config *tcfg;
	struct namedobj_instance *vi;
	struct table_value *pval, *valuestate, *old_valuestate;
	void *new_idx;
	struct vdump_args da;
	int new_blocks;
	int val_size, val_size_old;

	IPFW_UH_WLOCK_ASSERT(ch);

	valuestate = NULL;
	new_idx = NULL;

	pval = (struct table_value *)ch->valuestate;
	vi = CHAIN_TO_VI(ch);
	tcfg = CHAIN_TO_TCFG(ch);

	val_size = tcfg->val_size * 2;

	if (val_size == (1 << 30))
		return (ENOSPC);

	IPFW_UH_WUNLOCK(ch);

	valuestate = malloc(sizeof(struct table_value) * val_size, M_IPFW,
	    M_WAITOK | M_ZERO);
	ipfw_objhash_bitmap_alloc(val_size, (void *)&new_idx,
	    &new_blocks);

	IPFW_UH_WLOCK(ch);

	/*
	 * Check if we still need to resize
	 */
	if (tcfg->val_size >= val_size)
		goto done;

	/* Update pointers and notify everyone we're changing @ch */
	pval = (struct table_value *)ch->valuestate;
	rollback_toperation_state(ch, ch);

	/* Good. Let's merge */
	memcpy(valuestate, pval, sizeof(struct table_value) * tcfg->val_size);
	ipfw_objhash_bitmap_merge(CHAIN_TO_VI(ch), &new_idx, &new_blocks);

	IPFW_WLOCK(ch);
	/* Change pointers */
	old_valuestate = ch->valuestate;
	ch->valuestate = valuestate;
	valuestate = old_valuestate;
	ipfw_objhash_bitmap_swap(CHAIN_TO_VI(ch), &new_idx, &new_blocks);

	val_size_old = tcfg->val_size;
	tcfg->val_size = val_size;
	val_size = val_size_old;
	IPFW_WUNLOCK(ch);
	/* Update pointers to reflect resize */
	memset(&da, 0, sizeof(da));
	da.pval = (struct table_value *)ch->valuestate;
	ipfw_objhash_foreach(vi, update_tvalue, &da);

done:
	free(valuestate, M_IPFW);
	ipfw_objhash_bitmap_free(new_idx, new_blocks);

	return (0);
}