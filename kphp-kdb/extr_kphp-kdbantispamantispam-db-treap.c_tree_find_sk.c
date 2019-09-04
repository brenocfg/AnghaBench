#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trie_node_t ;
struct TYPE_3__ {int x; int /*<<< orphan*/ * data; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */

trie_node_t *tree_find_sk (tree_t *V, int x) {
  while (V && V->x != x) {
    V = (V->x > x ? V->left : V->right);
  }
  return V ? V->data : 0;
}