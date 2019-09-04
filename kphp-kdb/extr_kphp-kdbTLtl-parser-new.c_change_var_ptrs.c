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
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tl_type {int /*<<< orphan*/  id; } ;
struct tl_combinator_tree {scalar_t__ act; int data; struct tl_combinator_tree* right; struct tl_combinator_tree* left; } ;

/* Variables and functions */
 scalar_t__ act_field ; 
 scalar_t__ act_var ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int tl_get_var_value (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  tl_set_var_value (int /*<<< orphan*/ **,struct tl_combinator_tree*,struct tl_combinator_tree*) ; 
 struct tl_type* tl_tree_get_type (struct tl_combinator_tree*) ; 

void change_var_ptrs (struct tl_combinator_tree *O, struct tl_combinator_tree *D, tree_var_value_t **V) {
  if (!O || !D) {
    assert (!O && !D);
    return;
  }
  if (O->act == act_field) {
    struct tl_type *t = tl_tree_get_type (O->left);
    if (t && (!strcmp (t->id, "#") || !strcmp (t->id, "Type"))) {
      tl_set_var_value (V, O, D);
    }
  }
  if (O->act == act_var) {
    assert (D->data == O->data);
    D->data = tl_get_var_value (V, O->data);
    assert (D->data);
  }
  change_var_ptrs (O->left, D->left, V);
  change_var_ptrs (O->right, D->right, V);
}