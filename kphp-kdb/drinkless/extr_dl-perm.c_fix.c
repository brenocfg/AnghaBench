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
struct TYPE_9__ {scalar_t__ b; scalar_t__ a; struct TYPE_9__* p; struct TYPE_9__* r; struct TYPE_9__* l; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free_prm (TYPE_1__*) ; 
 int /*<<< orphan*/  dl_prm_fix (TYPE_1__*) ; 
 TYPE_1__* dl_prm_rev_del (TYPE_1__**,scalar_t__) ; 

void fix (dl_prm_ptr *a, dl_prm_ptr *b, dl_prm_ptr *rv) {
  if (*a && *b) {
    while ((*a)->r) {
      a = &(*a)->r;
    }
    while ((*b)->l) {
      b = &(*b)->l;
    }
    if ((*a)->b == (*b)->a) {
      dl_prm_ptr tmp = *b;
      *b = tmp->r;

      (*a)->b = tmp->b;

      dl_prm_fix (tmp->p);
      assert (dl_prm_rev_del (rv, tmp->a) == tmp);
      dl_free_prm (tmp);

      dl_prm_fix (*a);
    }
  }
}