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
 int /*<<< orphan*/  tree_delete_prefix (int /*<<< orphan*/ ,char const*,int,int,int) ; 
 int /*<<< orphan*/  wildcard_cache_tree ; 
 int /*<<< orphan*/  wildcard_rpc_cache_tree ; 

void  on_value_change (const char *key, int key_len) {
  wildcard_cache_tree = tree_delete_prefix (wildcard_cache_tree, key, key_len, 1, 1);
  wildcard_rpc_cache_tree = tree_delete_prefix (wildcard_rpc_cache_tree, key, key_len, 1, 1);
}