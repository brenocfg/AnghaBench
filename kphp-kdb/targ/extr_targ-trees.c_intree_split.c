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

inline void intree_split (treespace_t TS, treeref_t T, int x, treeref_t *L, treeref_t *R) {
  while (T) {
    struct intree_node *TP = TS_NODE(T);
    if (x < TP->x) {
      *R = T;
      T = TP->left;
      R = &TP->left;
    } else {
      *L = T;
      T = TP->right;
      L = &TP->right;
    }
  }
  *L = *R = 0;
}