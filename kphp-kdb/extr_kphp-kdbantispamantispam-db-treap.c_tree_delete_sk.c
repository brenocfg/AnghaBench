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
typedef  int /*<<< orphan*/  trie_node_t ;
struct TYPE_8__ {int x; int /*<<< orphan*/ * data; struct TYPE_8__* right; struct TYPE_8__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* tree_merge_sk (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

trie_node_t *tree_delete_sk (tree_t **V, int x) {
  tree_t *P;
  trie_node_t *res = 0;
  while (*V && (*V)->x != x)
    V = (x < (*V)->x ? &(*V)->left : &(*V)->right);
  assert (*V);

  P = tree_merge_sk ((*V)->left, (*V)->right);
  res = (*V)->data;
  zfree (*V, sizeof (tree_t));
  *V = P;
  return res;
}