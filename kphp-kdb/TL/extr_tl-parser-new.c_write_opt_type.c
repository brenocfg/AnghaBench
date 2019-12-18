#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tl_combinator_tree {int type; int /*<<< orphan*/  act; struct tl_combinator_tree* right; TYPE_1__* left; } ;
struct TYPE_2__ {int type_flags; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  act_arg ; 
 int /*<<< orphan*/  act_array ; 
 int /*<<< orphan*/  act_type ; 
 int /*<<< orphan*/  act_var ; 
 int /*<<< orphan*/  assert (struct tl_combinator_tree*) ; 
 int schema_version ; 
 int tl_get_var_value_num (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
#define  type_type 128 
 int /*<<< orphan*/  wint (int) ; 
 int /*<<< orphan*/  write_array (struct tl_combinator_tree*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  write_type_rec (struct tl_combinator_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 

void write_opt_type (struct tl_combinator_tree *T, tree_var_value_t **v, int *last_var) {
  if (schema_version >= 1) {
  } else {
    wint (-20);
  }
  wint (tl_get_var_value_num (v, T->left->data));
  wint (T->left->type_flags);
//  write_tree (T->right, 0, v, last_var);
  assert (T);
  T = T->right;
  switch (T->type) {
  case type_type:
    if (T->act == act_array) {
      write_array (T, v, last_var);
    } else if (T->act == act_type || T->act == act_var || T->act == act_arg) {
      write_type_rec (T, 0, v, last_var);
    } else {
      assert (0);
    }
    break;
  default:
    assert (0);
  }
}