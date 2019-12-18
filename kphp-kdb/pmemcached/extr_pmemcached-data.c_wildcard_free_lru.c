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
struct wildcard_entry {int flags; struct wildcard_entry* prev_use; } ;
typedef  int /*<<< orphan*/  hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tree_wildcard_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,struct wildcard_entry*) ; 
 int /*<<< orphan*/  wildcard_cache_memory ; 
 int /*<<< orphan*/  wildcard_cache_tree ; 
 int /*<<< orphan*/  wildcard_rpc_cache_tree ; 
 struct wildcard_entry wildcard_use ; 

void wildcard_free_lru (void) {
  struct wildcard_entry *entry = wildcard_use.prev_use;
  assert (entry != &wildcard_use);
  if (entry->flags & 1) {
    wildcard_cache_tree = tree_wildcard_delete (wildcard_cache_tree, (hash_entry_t *)entry);
  } else {
    wildcard_rpc_cache_tree = tree_wildcard_delete (wildcard_rpc_cache_tree, (hash_entry_t *)entry);
  }
  vkprintf (2, "wildcard_lru succ: memory = %lld, entry = %p\n", wildcard_cache_memory, entry);
}