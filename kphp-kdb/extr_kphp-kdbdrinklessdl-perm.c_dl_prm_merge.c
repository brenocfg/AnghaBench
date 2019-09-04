#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_10__ {scalar_t__ y; struct TYPE_10__* l; struct TYPE_10__* p; int /*<<< orphan*/  len; struct TYPE_10__* r; } ;

/* Variables and functions */
 scalar_t__ LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  fix (TYPE_1__**,TYPE_1__**,TYPE_1__**) ; 

void dl_prm_merge (dl_prm_ptr *tr, dl_prm_ptr a, dl_prm_ptr b, dl_prm_ptr *rv) {
  dl_prm_ptr p = NULL;

  fix (&a, &b, rv);

  while (a || b) {
    if (b == NULL || (a != NULL && a->y > b->y)) {
      a->len += LEN(b);

      a->p = p;
      p = a;

      *tr = a;
      tr = &a->r;
      a = a->r;
    } else {
      b->len += LEN(a);

      b->p = p;
      p = b;

      *tr = b;
      tr = &b->l;
      b = b->l;
    }
  }
  *tr = NULL;
}