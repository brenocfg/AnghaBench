#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_5__ {scalar_t__ x; scalar_t__ val; struct TYPE_5__* r; struct TYPE_5__* l; } ;

/* Variables and functions */
 TYPE_3__* gd_a ; 
 TYPE_3__* gd_b ; 
 int /*<<< orphan*/  insert_to_add (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  insert_to_del (scalar_t__) ; 

void gen_diff_go (treap_node_ptr v) {
  if (v == NULL) {
    return;
  }
  gen_diff_go (v->l);

  while (gd_a != gd_b && gd_a->x > v->x) {
    insert_to_add (gd_a->x, gd_a->y);
    gd_a++;
  }
  if (gd_a == gd_b || gd_a->x != v->x) {
    insert_to_del (v->x);
  } else {
    if (gd_a->y != v->val) {
      insert_to_add (gd_a->x, gd_a->y);
    }
    gd_a++;
  }

  gen_diff_go (v->r);
}