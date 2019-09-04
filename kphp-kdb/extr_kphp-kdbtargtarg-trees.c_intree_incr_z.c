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
typedef  int /*<<< orphan*/  treeref_t ;
struct intree_node {int x; int z; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 struct intree_node* TS_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_intree_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intree_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_intree_node (int /*<<< orphan*/ ) ; 

inline treeref_t intree_incr_z (treespace_t TS, treeref_t T, int x, int dz, int *nodes_num) {
  treeref_t Q = T, *QP = &Q;
  if (!dz) {
    return T;
  }
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
    TC->z += dz;
    if (!TC->z) {
      *QP = intree_merge (TS, TC->left, TC->right);
      free_intree_node (TS, T);
      --*nodes_num;
    }
    return Q;
  } 

  T = new_intree_node (TS);
  struct intree_node *TC = TS_NODE(T);
  TC->x = x;
  TC->z = dz;
  ++*nodes_num;
  return intree_insert (TS, Q, T);
}