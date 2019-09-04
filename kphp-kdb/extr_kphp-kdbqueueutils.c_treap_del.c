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
typedef  scalar_t__ ll ;
struct TYPE_8__ {scalar_t__ x; int y; struct TYPE_8__* l; struct TYPE_8__* r; } ;

/* Variables and functions */
 TYPE_1__* free_nodes ; 
 int /*<<< orphan*/  free_nodes_cnt ; 
 int /*<<< orphan*/  treap_merge (TYPE_1__**,TYPE_1__*,TYPE_1__*) ; 

int treap_del (treap *tr, ll x) {
  treap_node_ptr *v = &tr->root;

  while (*v != NULL) {
    if ((*v)->x  == x) {
      treap_node_ptr t = *v;
      treap_merge (v, t->l, t->r);

      t->r = NULL;
      t->l = free_nodes;
      free_nodes = t;
      free_nodes_cnt++;
      tr->size++;

      return t->y;
    } else if ((*v)->x > x) {
      v = &(*v)->r;
    } else if ((*v)->x < x) {
      v = &(*v)->l;
    }
  }
  return 0;
}