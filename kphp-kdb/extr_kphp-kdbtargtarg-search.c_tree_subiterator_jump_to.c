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
struct tree_subiterator {int pos; long sp; void** S; int /*<<< orphan*/  mult; } ;
struct intree_node {int x; int /*<<< orphan*/  z; void* right; void* left; } ;

/* Variables and functions */
 int INFTY ; 
 long MAX_DEPTH ; 
 struct intree_node* TS_NODE (void*) ; 
 int /*<<< orphan*/  WordSpace ; 
 int /*<<< orphan*/  assert (int) ; 
 int tree_subiterator_next (struct tree_subiterator*) ; 

int tree_subiterator_jump_to (struct tree_subiterator *TI, int req_pos) {
  if (req_pos == TI->pos + 1) {
    return tree_subiterator_next (TI);
  }
  assert (req_pos > TI->pos && TI->sp > 0);
  long i = TI->sp;
  treespace_t TS = WordSpace;
  struct intree_node *TC;
  treeref_t T;
  while (i > 1 && TS_NODE (TI->S[i-2])->x <= req_pos) {
    i--;
  }
  TC = TS_NODE (TI->S[i-1]);
  if (TC->x == req_pos) {
    TI->sp = i;
    TI->mult = TC->z;
    return TI->pos = req_pos;
  }
  i--;
  T = TC->right;
  while (T) {
    TC = TS_NODE (T);
    if (req_pos < TC->x) {
      TI->S[i++] = T;
      T = TC->left;
    } else if (req_pos == TC->x) {
      TI->S[i++] = T;
      TI->sp = i;
      TI->mult = TC->z;
      return TI->pos = req_pos;
    } else {
      T = TC->right;
    }
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