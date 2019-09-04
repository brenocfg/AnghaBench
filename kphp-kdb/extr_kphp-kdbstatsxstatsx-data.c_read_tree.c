#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* new_tree_node (int,int) ; 
 scalar_t__ readin_char () ; 
 int readin_int () ; 

tree_t* read_tree () {
  if (readin_char () == 0) {
    return 0;
  }
  int x = readin_int ();
  int y = readin_int ();
  tree_t *P = new_tree_node (x, y);
  P->left = read_tree ();
  P->right = read_tree ();
  if (P->left) { assert (P->left->x < P->x); }
  if (P->right) { assert (P->right->x > P->x); }
  return P;
}