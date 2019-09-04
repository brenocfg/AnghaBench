#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* extra; int x1; int x2; struct TYPE_6__* right; struct TYPE_6__* middle; struct TYPE_6__* left; } ;
typedef  TYPE_1__ tree23_t ;
struct TYPE_7__ {int extra_words; int depth; TYPE_1__* root; } ;
typedef  TYPE_2__ tree23_root_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 void* new_leaf (int,int) ; 
 void* new_node2 (int,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void tree23_insert (tree23_root_t *R, int x, int *Data) {
  tree23_t *st[40];
  int x_Data[8];
  tree23_t *cur, *s, *l;
  int sp, extra_words = R->extra_words;

#define Extra_words	extra_words
#define x1_Data		extra-Extra_words
#define x2_Data		extra-Extra_words*2
#define DATA(__x)	(__x##_Data)
#define	CPY(__x,__y)	{if(Extra_words>0) {memcpy(__x,__y,Extra_words*4);}}
#define DCPY(__x,__y)	CPY(DATA(__x),DATA(__y))
#define	LET(__x,__y)	{__x = __y; DCPY(__x,__y);}
#define IS_2N(__t)	((__t)->x1 == (__t)->x2)
#define IS_3N(__t)	(!IS_2N(__t))
#define LEAF(__t)	((tree23_leaf_t *)(__t))

  //empty tree case
  if (!R->root) {
    R->root = new_leaf (x, extra_words);
    CPY(DATA(R->root->x1), Data);
    R->depth = 0;
    return;
  }

  sp = 0;
  cur = R->root;
  while (sp < R->depth) {
    st[sp++] = cur;
    if (x < cur->x1) {
      cur = cur->left;
    } else if (x > cur->x2) {
      cur = cur->right;
    } else {
      cur = cur->middle;
    }
  }
  
  //leaf split
  if (IS_3N(cur)) {
    //case 1. two-element leaf: have cur:[ B D ]
    if (x < cur->x1) {
      // cur:[ B D ] + x:A --> [ A B D ] --> (new)s:[ A ] new_x:B (cur)l:[ D ]
      s = new_leaf (x, Extra_words);
      CPY (DATA(s->x1), Data)
      LET (x, cur->x1);
      LET (cur->x1, cur->x2);
      l = cur;
    } else if (x > cur->x2) {
      // cur:[ B D ] + x:E --> [ A D E ] --> (cur)s:[ B ] new_x:D (new)l:[ E ]
      l = new_leaf (x, Extra_words);
      CPY (DATA(l->x1), Data)
      LET (x, cur->x2)
      cur->x2 = cur->x1;
      s = cur;
    } else {
      // cur:[ B D ] + x:C --> [ A C E ] --> (cur)s:[ B ] new_x:C (new)l:[ D ]
      l = new_leaf (cur->x2, Extra_words);
      CPY (DATA(l->x1), DATA(cur->x2))
      CPY (DATA(x), Data);
      cur->x2 = cur->x1;
      s = cur;
    }
  } else {
    //case 2. single-element leaf:  have cur:[ B ]
    if (x < cur->x1) {
      // cur:[ B ] + x:A --> cur:[ A B ]
      LET (cur->x2, cur->x1);
      cur->x1 = x;
      CPY (DATA(cur->x1), Data);
    } else {
      // cur:[ B ] + x:C --> cur:[ B C ]
      cur->x2 = x;
      CPY (DATA(cur->x2), Data);
    }
    return;
  }

  while (sp) {
    cur = st[--sp];
    // here cur is a parent node cur: [ ... old_cur:[.E.G.] ... ]
    // we are replacing its subtree [.E.G.] with two: s:[.E.] x:F l:[.G.]
    if (IS_3N(cur)) {
      //case 1. two-element internal node
      // cur: [ (left) x1 (middle) x2 (right) ]
      if (x < cur->x1) {
        // s l middle right
        // cur: [ old_cur:[.E.G.] x1:H [.I.] x2:J [.K.] ]
        // -->  [ s:[.E.] x:F l:[.G.] x1:H [.I.] J [.K.] ]
        // -->  (new)new_s:[ s:[.E.] x:F l:[.G.] ] new_x:H (cur)new_l:[ [.I.] J [.K.] ]
        s = new_node2 (x, s, l, Extra_words);
        DCPY(s->x1, x);
        LET (x, cur->x1);
        LET (cur->x1, cur->x2);
        cur->left = cur->middle;
        l = cur;
      } else
      if (x > cur->x2) {
        // left middle s l
        // cur: [ [.A.] B [.C.] D old_cur:[.E.G.] ]
        // -->  [ [.A.] x1:B [.C.] x2:D s:[.E.] x:F l:[.G.] ]
        // -->  (cur)new_s:[ [.A.] x1:B [.C.] ] new_x:D (new)new_l:[ s:[.E.] x:F l:[.G.] ]
        l = new_node2 (x, s, l, Extra_words);
        DCPY(l->x1, x);
        LET (x, cur->x2);
        cur->right = cur->middle;
        cur->x2 = cur->x1;
        s = cur;
      } else {
        //left s l right
        // cur: [ [.C.] x1:D old_cur:[.E.G.] x2:H [.I.] ]
        // --> [ [.C.] x1:D s:[.E.] x:F l:[.G.] x2:H [.I.] ]
        // --> (cur)new_s:[ [.C.] x1:D s:[.E.] ] new_x:F (new)new_l:[l:[.G.] x2:H [.I.] ]
        l = new_node2 (cur->x2, l, cur->right, Extra_words);
        DCPY(l->x1, cur->x2);
        cur->right = s;
        cur->x2 = cur->x1;
        s = cur;
      }
    } else {
      //case 2. single-element internal node
      // cur: [ (left) x1=x2 (right) ]
      if (x < cur->x1) {
        // s l right
        // cur: [ old_cur:[.E.G.] x1:H [.I.] ]
        // -->  [ s:[.E.] x:F l:[.G.] x1:H [.I.] ]
        cur->left = s;
        cur->middle = l;
        cur->x1 = x;
        DCPY(cur->x2, cur->x1);
        DCPY(cur->x1, x);
      } else {
        //left s l 
        // cur: [ [.C.] x1:D old_cur:[.E.G.] ]
        // -->  [ [.C.] x1:D s:[.E.] x:F l:[.G.] ]
        cur->middle = s;
        cur->right = l;
        LET(cur->x2, x);
      }
      return;
    }

  }

  //root split
  // here  s:[.E.] x:F l:[.G.] comes to the top
  // create new root [ [.E.] F [.G.] ]
  R->root = new_node2 (x, s, l, Extra_words);
  R->depth++;
  CPY (DATA(R->root->x1), Data);
}