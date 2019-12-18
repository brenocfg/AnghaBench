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
struct item {int type; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  item_tree ; 
 int /*<<< orphan*/  tree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,struct item*) ; 

void change_node_type (struct item *I, int new_type) {
  item_tree = tree_delete (item_tree, I->key_len, I->key);
  I->type = (I->type & ~7) | new_type;
  item_tree = tree_insert (item_tree, I);
}