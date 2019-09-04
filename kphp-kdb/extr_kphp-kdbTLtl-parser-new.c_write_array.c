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
struct tl_combinator_tree {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int TLS_ARRAY ; 
 int TLS_TREE_ARRAY ; 
 int schema_version ; 
 int /*<<< orphan*/  wint (int) ; 
 int /*<<< orphan*/  write_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 

void write_array (struct tl_combinator_tree *T, tree_var_value_t **v, int *last_var) {
  if (schema_version == 1) {
    wint (TLS_TREE_ARRAY);
  } else if (schema_version == 2) {
    wint (TLS_ARRAY);
  } else {
    wint (-8);
  }
  write_tree (T->left, 0, v, last_var);
  write_tree (T->right, 0, v, last_var);
}