#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_9__ {int /*<<< orphan*/  size; TYPE_1__* root; } ;
typedef  TYPE_2__ treap ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_8__ {int y; int val; struct TYPE_8__* r; struct TYPE_8__* l; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 TYPE_1__* get_new_node () ; 
 int /*<<< orphan*/  treap_split (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__**) ; 

void treap_add (treap *tr, ll x, int val, int y) {
  treap_node_ptr *v = &tr->root;

  while (*v != NULL && ((*v)->y >= y)) {
    if ((*v)->x == x) {
      (*v)->val = val;
      return;
    } else if ((*v)->x > x) {
      v = &(*v)->r;
    } else if ((*v)->x < x) {
      v = &(*v)->l;
    }
  }
  treap_node_ptr vv = *v;

  while (vv != NULL) {
    if (vv->x == x) {
      vv->val = val;
      return;
    } else if (vv->x > x) {
      vv = vv->r;
    } else if (vv->x < x) {
      vv = vv->l;
    }
  }

  treap_node_ptr u = get_new_node();
  tr->size--;
  u->x = x;
  u->val = val;
  u->y = y;
  treap_split (*v, x, &u->l, &u->r);
  *v = u;
}