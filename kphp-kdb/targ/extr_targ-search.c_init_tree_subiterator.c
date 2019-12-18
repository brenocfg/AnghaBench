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
typedef  int treeref_t ;
struct tree_subiterator {int* S; long sp; int /*<<< orphan*/  mult; int /*<<< orphan*/  pos; } ;
struct intree_node {int left; int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 long MAX_DEPTH ; 
 struct intree_node* TS_NODE (int) ; 
 int /*<<< orphan*/  WordSpace ; 
 int /*<<< orphan*/  assert (int) ; 

void init_tree_subiterator (struct tree_subiterator *TI, treeref_t tree) {
  assert (tree);
  long i = 0;
  treespace_t TS = WordSpace;
  struct intree_node *TC;
  do {
    TC = TS_NODE (tree);
    TI->S[i++] = tree;
    tree = TC->left;
  } while (tree);
  TI->pos = TC->x;
  TI->mult = TC->z;
  TI->sp = i;
  assert (i <= MAX_DEPTH);
}