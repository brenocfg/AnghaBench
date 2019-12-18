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
typedef  void* treeref_t ;
struct intree_node {void* right; void* left; } ;

/* Variables and functions */
 unsigned int NODE_Y (struct intree_node*,void*) ; 
 struct intree_node* TS_NODE (void*) ; 

inline treeref_t intree_merge (treespace_t TS, treeref_t L, treeref_t R) {
  treeref_t T, *TP = &T;
  struct intree_node *LP, *RP;
  unsigned LY, RY;
  if (!L) {
    return R;
  }
  if (!R) {
    return L;
  }
  LP = TS_NODE(L);
  LY = NODE_Y(LP, L);
  RP = TS_NODE(R);
  RY = NODE_Y(RP, R);
  while (1) {
    if (LY > RY) {
      *TP = L;
      L = LP->right;
      if (!L) {
        LP->right = R;
        return T;
      }
      TP = &LP->right;
      LP = TS_NODE(L);
      LY = NODE_Y(LP, L);
    } else {
      *TP = R;
      R = RP->left;
      if (!R) {
        RP->left = L;
        return T;
      }
      TP = &RP->left;
      RP = TS_NODE(R);
      RY = NODE_Y(RP, R);
    }
  }
}