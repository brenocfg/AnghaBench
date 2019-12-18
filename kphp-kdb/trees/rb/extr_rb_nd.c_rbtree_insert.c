#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int x; struct TYPE_7__* left; struct TYPE_7__* right; } ;
typedef  TYPE_1__ rbtree_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKEN (TYPE_1__*) ; 
 scalar_t__ IS_BLACK (TYPE_1__*) ; 
 TYPE_1__* new_node (int,int,int*) ; 

__attribute__((used)) static rbtree_t *rbtree_insert (rbtree_t *Root, int x, int extra, int *Data) {
  rbtree_t *st[70];
  rbtree_t *T, *N, *U;
  int sp;

  x <<= 1;

  //empty tree case
  if (!Root) {
    return new_node (x, extra, Data);
  }

  sp = 0;
  T = Root;
  while (T) {
    st[sp++] = T;
    if (T->x < x) {
      T = T->right;
    } else if (T->x > x + 1) {
      T = T->left;
    } else {
// x already there ...
      return T;
    }
  }

  N = new_node (x+1, extra, Data);

  while (sp > 0) {
    T = st[--sp];
    // one of subtrees of T is to be replaced with RED N
    // after that, tree would be RB unless T is also RED
    if (x < T->x) {
      // N replaces left subtree of T
      if (IS_BLACK(T)) {
        // if T is BLACK, we are done
        T->left = N;
        return Root;
      }
      if (!sp) {
        // if T is RED and is the root, simply make it BLACK
        BLACKEN(T);
        T->left = N;
        return Root;
      }
      U = st[--sp];
      // here T is RED, so its parent U must be BLACK
      if (x < U->x) {
        // T is the left subtree of U
        // now U:[ T:{ N:{.x.} y.} z (right) ]
        // --> new_U=T:{ N:[.x.] y [.z (right) ]}
        U->left = T->right;
        T->right = U;
        BLACKEN(N);
        N = U;
      } else {
        // now U:[ T:{.u N:{.x.}} y (right) ]
        // --> new_U=N:{ T:[.u.] x U:[.y (right) ]}
        T->right = N->left;
        BLACKEN(T);
        N->left = T;
        U->left = N->right;
        N->right = U;
      }
    } else {
      // N replaces right subtree of T
      if (IS_BLACK(T)) {
        // if T is BLACK, we are done
        T->right = N;
        return Root;
      }
      if (!sp) {
        // if T is RED and is the root, simply make it BLACK
        BLACKEN(T);
        T->right = N;
        return Root;
      }
      U = st[--sp];
      // here T is RED, so its parent U must be BLACK
      if (x < U->x) {
        // now U:[ (left) u T:{ N:{.x.} y.} ]
        // --> new_U=N:{ U:[.u.] x T:[.y.]}
        T->left = N->right;
        BLACKEN(T);
        N->right = T;
        U->right = N->left;
        N->left = U;
      } else {
        // now U:[ (left) u T:{.v N:{.x.} } ]
        // --> new_U=T:{ U:[(left) u.] v N:[.x.]}
        U->right = T->left;
        T->left = U;
        BLACKEN(N);
        N = T;
      }
    }
  }
  // if we come here, the whole tree is to be replaced with N
  return N;
}