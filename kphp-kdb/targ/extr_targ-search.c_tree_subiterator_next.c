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
struct tree_subiterator {long sp; int pos; int /*<<< orphan*/  mult; scalar_t__* S; } ;
struct intree_node {int x; int /*<<< orphan*/  z; scalar_t__ left; scalar_t__ right; } ;

/* Variables and functions */
 int INFTY ; 
 long MAX_DEPTH ; 
 struct intree_node* TS_NODE (scalar_t__) ; 
 int /*<<< orphan*/  WordSpace ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int tree_subiterator_next (struct tree_subiterator *TI) {
  assert (TI->sp > 0);
  long i = TI->sp;
  treespace_t TS = WordSpace;
  treeref_t T = TI->S[--i];
  struct intree_node *TC = TS_NODE (T);
  T = TC->right;
  while (T) {
    TC = TS_NODE (T);
    TI->S[i++] = T;
    T = TC->left;
  }
  assert (i <= MAX_DEPTH);
  TI->sp = i;
  if (!i) {
    return TI->pos = INFTY;
  }
  TC = TS_NODE (TI->S[i - 1]);
  TI->mult = TC->z;
  return TI->pos = TC->x;
}