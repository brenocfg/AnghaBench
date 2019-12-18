#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_6__ {TYPE_1__* root; } ;
typedef  TYPE_2__ treap ;
typedef  scalar_t__ ll ;
struct TYPE_5__ {scalar_t__ x; struct TYPE_5__* l; struct TYPE_5__* r; } ;

/* Variables and functions */

treap_node_ptr treap_fnd (treap *t, ll x) {
  treap_node_ptr v = t->root;

  while (v != NULL) {
    if (v->x == x) {
      return v;
    } else if (v->x > x) {
      v = v->r;
    } else if (v->x < x) {
      v = v->l;
    }
  }
  return NULL;
}