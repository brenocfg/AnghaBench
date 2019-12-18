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
 int addr_tree_compare (void const*,void const*) ; 
 int anchor_cmp (void const*,void const*) ; 
 int auth_data_cmp (void const*,void const*) ; 
 int auth_xfer_cmp (void const*,void const*) ; 
 int auth_zone_cmp (void const*,void const*) ; 
 int canonical_tree_compare (void const*,void const*) ; 
 int codeline_cmp (void const*,void const*) ; 
 int context_query_cmp (void const*,void const*) ; 
 int fwd_cmp (void const*,void const*) ; 
 int local_data_cmp (void const*,void const*) ; 
 int local_zone_cmp (void const*,void const*) ; 
 int mesh_state_compare (void const*,void const*) ; 
 int mesh_state_ref_compare (void const*,void const*) ; 
 int mini_ev_cmp (void const*,void const*) ; 
 int name_tree_compare (void const*,void const*) ; 
 int nsec3_hash_cmp (void const*,void const*) ; 
 int order_lock_cmp (void const*,void const*) ; 
 int pending_cmp (void const*,void const*) ; 
 int probetree_cmp (void const*,void const*) ; 
 int replay_var_compare (void const*,void const*) ; 
 int serviced_cmp (void const*,void const*) ; 
 int val_neg_data_compare (void const*,void const*) ; 
 int val_neg_zone_compare (void const*,void const*) ; 
 int view_cmp (void const*,void const*) ; 

int 
fptr_whitelist_rbtree_cmp(int (*fptr) (const void *, const void *))
{
	if(fptr == &mesh_state_compare) return 1;
	else if(fptr == &mesh_state_ref_compare) return 1;
	else if(fptr == &addr_tree_compare) return 1;
	else if(fptr == &local_zone_cmp) return 1;
	else if(fptr == &local_data_cmp) return 1;
	else if(fptr == &fwd_cmp) return 1;
	else if(fptr == &pending_cmp) return 1;
	else if(fptr == &serviced_cmp) return 1;
	else if(fptr == &name_tree_compare) return 1;
	else if(fptr == &order_lock_cmp) return 1;
	else if(fptr == &codeline_cmp) return 1;
	else if(fptr == &nsec3_hash_cmp) return 1;
	else if(fptr == &mini_ev_cmp) return 1;
	else if(fptr == &anchor_cmp) return 1;
	else if(fptr == &canonical_tree_compare) return 1;
	else if(fptr == &context_query_cmp) return 1;
	else if(fptr == &val_neg_data_compare) return 1;
	else if(fptr == &val_neg_zone_compare) return 1;
	else if(fptr == &probetree_cmp) return 1;
	else if(fptr == &replay_var_compare) return 1;
	else if(fptr == &view_cmp) return 1;
	else if(fptr == &auth_zone_cmp) return 1;
	else if(fptr == &auth_data_cmp) return 1;
	else if(fptr == &auth_xfer_cmp) return 1;
	return 0;
}