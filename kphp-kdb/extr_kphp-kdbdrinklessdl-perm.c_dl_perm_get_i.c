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
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_6__ {int len; TYPE_1__* v; } ;
typedef  TYPE_2__ dl_perm ;
struct TYPE_5__ {int b; int a; struct TYPE_5__* r; struct TYPE_5__* l; } ;

/* Variables and functions */
 int LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int dl_perm_get_i (dl_perm *p, int i) {
  if (!(0 <= i && i < p->len)) {
    return -1;
  }
  dl_prm_ptr v = p->v;
  while (v != NULL) {
    int xn = LEN(v->l);
    if (i < xn) {
      v = v->l;
    } else {
      i -= xn;
      if (i < v->b - v->a) {
        return v->a + i;
      }
      i -= v->b - v->a;
      v = v->r;
    }
  }
  assert (0);
}