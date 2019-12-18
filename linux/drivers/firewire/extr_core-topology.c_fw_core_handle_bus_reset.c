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
struct fw_node {int dummy; } ;
struct fw_card {int generation; int node_id; int bm_node_id; int bm_abdicate; int /*<<< orphan*/  lock; struct fw_node* local_node; int /*<<< orphan*/  color; int /*<<< orphan*/  reset_jiffies; int /*<<< orphan*/  broadcast_channel_auto_allocated; int /*<<< orphan*/  broadcast_channel_allocated; scalar_t__ bm_retries; } ;

/* Variables and functions */
 struct fw_node* build_tree (struct fw_card*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  for_each_fw_node (struct fw_card*,struct fw_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_destroy_nodes (struct fw_card*) ; 
 int /*<<< orphan*/  fw_err (struct fw_card*,char*) ; 
 int /*<<< orphan*/  fw_schedule_bm_work (struct fw_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  is_next_generation (int,int) ; 
 int /*<<< orphan*/  report_found_node ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_topology_map (struct fw_card*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_tree (struct fw_card*,struct fw_node*) ; 

void fw_core_handle_bus_reset(struct fw_card *card, int node_id, int generation,
			      int self_id_count, u32 *self_ids, bool bm_abdicate)
{
	struct fw_node *local_node;
	unsigned long flags;

	/*
	 * If the selfID buffer is not the immediate successor of the
	 * previously processed one, we cannot reliably compare the
	 * old and new topologies.
	 */
	if (!is_next_generation(generation, card->generation) &&
	    card->local_node != NULL) {
		fw_destroy_nodes(card);
		card->bm_retries = 0;
	}

	spin_lock_irqsave(&card->lock, flags);

	card->broadcast_channel_allocated = card->broadcast_channel_auto_allocated;
	card->node_id = node_id;
	/*
	 * Update node_id before generation to prevent anybody from using
	 * a stale node_id together with a current generation.
	 */
	smp_wmb();
	card->generation = generation;
	card->reset_jiffies = get_jiffies_64();
	card->bm_node_id  = 0xffff;
	card->bm_abdicate = bm_abdicate;
	fw_schedule_bm_work(card, 0);

	local_node = build_tree(card, self_ids, self_id_count);

	update_topology_map(card, self_ids, self_id_count);

	card->color++;

	if (local_node == NULL) {
		fw_err(card, "topology build failed\n");
		/* FIXME: We need to issue a bus reset in this case. */
	} else if (card->local_node == NULL) {
		card->local_node = local_node;
		for_each_fw_node(card, local_node, report_found_node);
	} else {
		update_tree(card, local_node);
	}

	spin_unlock_irqrestore(&card->lock, flags);
}