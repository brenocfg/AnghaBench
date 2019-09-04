#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_9__ {int a; int b; int len; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* dl_alloc_prm () ; 
 int /*<<< orphan*/  dl_prm_rev_add (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  rand () ; 

void dl_prm_split_node (dl_prm_ptr v, dl_prm_ptr *a, dl_prm_ptr *b, int x, dl_prm_ptr *rv) {
  x += v->a;
  if (x == v->a) {
    *a = NULL;
    *b = v;
  } else if (x == v->b) {
    *a = v;
    *b = NULL;
  } else if (v->a < x && x < v->b) {
    *b = dl_alloc_prm();
    (*b)->a = x;
    (*b)->b = v->b;
    (*b)->y = rand();
    (*b)->len = (*b)->b - (*b)->a;

    *a = v;
    (*a)->b = x;
    (*a)->len = (*a)->b - (*a)->a;

    dl_prm_rev_add (rv, *b);
  } else {
    assert (0);
  }
}