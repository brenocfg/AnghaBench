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
typedef  int /*<<< orphan*/  treespace_t ;
typedef  scalar_t__ treeref_t ;
struct intree_node {int x; scalar_t__ right; scalar_t__ left; } ;

/* Variables and functions */
 struct intree_node* TS_NODE (scalar_t__) ; 
 scalar_t__ intree_merge (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

inline treeref_t intree_remove (treespace_t TS, treeref_t T, int x, treeref_t *N) {
  treeref_t Q = T, *QP = &Q;
  while (T) {
    struct intree_node *TC = TS_NODE(T);
    if (x == TC->x) {
      break;
    }
    if (x < TC->x) {
      QP = &TC->left;
      T = TC->left;
    } else {
      QP = &TC->right;
      T = TC->right;
    }
  }
  if (T) {
    struct intree_node *TC = TS_NODE(T);
    *QP = intree_merge (TS, TC->left, TC->right);
  }
  *N = T;
  return Q;
}