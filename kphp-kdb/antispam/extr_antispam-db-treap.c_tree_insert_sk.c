#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trie_node_t ;
struct TYPE_7__ {int y; int x; struct TYPE_7__* right; struct TYPE_7__* left; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int lrand48 () ; 
 TYPE_1__* new_tree_node (int,int) ; 
 int /*<<< orphan*/  tree_split_sk (TYPE_1__**,TYPE_1__**,TYPE_1__*,int) ; 

void tree_insert_sk (tree_t **V, int x, trie_node_t *v) {
  tree_t *P;
  int y = lrand48();
  while (*V && (*V)->y >= y) {
    V = (x < (*V)->x ? &(*V)->left : &(*V)->right);
  }
  P = new_tree_node (x, y);
  P->data = v;
  tree_split_sk (&P->left, &P->right, *V, x);
  *V = P;
}