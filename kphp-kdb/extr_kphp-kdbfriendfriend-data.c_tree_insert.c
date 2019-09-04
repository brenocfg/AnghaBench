#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int cat; int date; int x; int y; struct TYPE_8__* right; struct TYPE_8__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* new_tree_node (int,int) ; 
 int /*<<< orphan*/  tree_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,int) ; 

__attribute__((used)) static tree_t *tree_insert (tree_t *T, int x, int y, int cat, int date) {
  tree_t *P;
  if (!T) { 
    P = new_tree_node (x, y);
    P->cat = cat;
    P->date = date;
    return P;
  }
  assert (x != T->x);
  if (T->y >= y) {
    if (x < T->x) {
      T->left = tree_insert (T->left, x, y, cat, date);
    } else {
      T->right = tree_insert (T->right, x, y, cat, date);
    }
    return T;
  }
  P = new_tree_node (x, y);
  P->cat = cat;
  P->date = date;
  tree_split (&P->left, &P->right, T, x);
  return P;
}