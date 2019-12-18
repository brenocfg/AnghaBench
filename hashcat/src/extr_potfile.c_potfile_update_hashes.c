#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* nodes; int /*<<< orphan*/ * hashconfig; } ;
typedef  TYPE_1__ pot_tree_entry_t ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/ * hash_buf; } ;
typedef  TYPE_2__ pot_hash_node_t ;
typedef  int /*<<< orphan*/  hashconfig_t ;
struct TYPE_10__ {int /*<<< orphan*/ * hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  potfile_update_hash (TYPE_3__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sort_pot_tree_by_hash ; 
 scalar_t__ tfind (TYPE_1__*,void**,int /*<<< orphan*/ ) ; 

void potfile_update_hashes (hashcat_ctx_t *hashcat_ctx, hash_t *hash_buf, char *line_pw_buf, int line_pw_len, pot_tree_entry_t *tree)
{
  hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  // the linked list node:

  pot_hash_node_t search_node;

  search_node.hash_buf = hash_buf;
  search_node.next     = NULL;

  // the search entry:

  pot_tree_entry_t search_entry;

  search_entry.nodes      = &search_node;
  search_entry.hashconfig = hashconfig;

  // the main search function is this:

  void **found = (void **) tfind (&search_entry, (void **) &tree, sort_pot_tree_by_hash);

  if (found)
  {
    pot_tree_entry_t *found_entry = (pot_tree_entry_t *) *found;

    pot_hash_node_t *node = found_entry->nodes;

    while (node)
    {
      potfile_update_hash (hashcat_ctx, node->hash_buf, line_pw_buf, line_pw_len);

      node = node->next;
    }
  }
}