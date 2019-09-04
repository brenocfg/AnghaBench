#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_5__ {int n; TYPE_1__* rv; } ;
typedef  TYPE_2__ dl_perm ;
struct TYPE_4__ {int a; int b; struct TYPE_4__* xr; int /*<<< orphan*/  l; struct TYPE_4__* r; struct TYPE_4__* p; struct TYPE_4__* xl; } ;

/* Variables and functions */
 int LEN (int /*<<< orphan*/ ) ; 

int dl_perm_get_rev_i (dl_perm *p, int i) {
  if (!(0 <= i && i < p->n)) {
    return -1;
  }
  //fprintf (stderr, "get rev : %d\n", i);
  //_go_rev (p->rv, 0);
  dl_prm_ptr v = p->rv, u;
  while (v != NULL) {
    if (i < v->a) {
      v = v->xl;
    } else if (i < v->b) {
      //fprintf (stderr, "node located [%d;%d]\n", v->a, v->b);
      int res = i - v->a + LEN (v->l);
      while ((u = v->p) != NULL) {
        if (u->r == v) {
          res += LEN(u->l) + u->b - u->a;
        }
        v = u;
      }
      //fprintf (stderr, "res = %d\n", res);
      return res;
    } else {
      v = v->xr;
    }
  }
  return -1;
//  assert (0);
}