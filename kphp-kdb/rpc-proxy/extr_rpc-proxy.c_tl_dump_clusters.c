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
 scalar_t__* __cluster_count ; 
 int /*<<< orphan*/  dump_cluster_id ; 
 int /*<<< orphan*/  rpc_cluster_tree ; 
 scalar_t__* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tree_act_rpc_cluster (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tl_dump_clusters (void) {
  __cluster_count = tl_store_get_ptr (4);
  *__cluster_count = 0;
  tree_act_rpc_cluster (rpc_cluster_tree, dump_cluster_id);
}