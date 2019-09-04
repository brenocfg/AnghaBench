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
typedef  int /*<<< orphan*/  pot_tree_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  sort_pot_tree_by_hash ; 
 int /*<<< orphan*/  tdelete (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 

void pot_tree_destroy (pot_tree_entry_t *tree)
{
  pot_tree_entry_t *entry = tree;

  while (tree != NULL)
  {
    entry = *(pot_tree_entry_t **) tree;

    tdelete (entry, (void **) &tree, sort_pot_tree_by_hash);
  }
}