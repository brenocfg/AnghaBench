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
struct tl_combinator_tree {scalar_t__ act; void* data; struct tl_combinator_tree* right; struct tl_combinator_tree* left; } ;

/* Variables and functions */
 scalar_t__ act_var ; 
 struct tl_combinator_tree* tl_get_var_value (int /*<<< orphan*/ **,void*) ; 

int tl_tree_lookup_value (struct tl_combinator_tree *L, void *var, tree_var_value_t **T) {
  if (!L) {
    return -1;
  }
  if (L->act == act_var && L->data == var) {
    return 0;
  }
  if (L->act == act_var) {
    struct tl_combinator_tree *E = tl_get_var_value (T, L->data);
    if (!E) { return -1;}
    else { return tl_tree_lookup_value (E, var, T); }
  }
  if (tl_tree_lookup_value (L->left, var, T) >= 0) { return 1; }
  if (tl_tree_lookup_value (L->right, var, T) >= 0) { return 1; }
  return -1;
}