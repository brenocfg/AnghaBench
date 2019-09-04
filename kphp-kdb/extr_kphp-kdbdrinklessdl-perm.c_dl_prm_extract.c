#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_8__ {int b; int a; int len; struct TYPE_8__* r; struct TYPE_8__* p; struct TYPE_8__* l; } ;

/* Variables and functions */
 int LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_prm_fix (TYPE_1__*) ; 

void dl_prm_extract (dl_prm_ptr v, dl_prm_ptr *a, dl_prm_ptr *b, dl_prm_ptr *m, int x) {
  assert (v != NULL);

  dl_prm_ptr pa = NULL, pb = NULL;

  while (v != NULL) {
//    fprintf (stderr, "v = %p\n", v);
    int xn = LEN(v->l);
    if (x < xn) {
      v->p = pb;
      pb = v;

      *b = v;
      b = &v->l;
      v = v->l;
    } else {
      x -= xn;
      if (x < v->b - v->a) {
        //found
        *a = v->l;
        if (*a) {
          (*a)->p = pa;
        }

        *b = v->r;
        if (*b) {
          (*b)->p = pb;
        }

        *m = v;
        v->l = v->r = v->p = NULL;
        v->len = v->b - v->a;

        dl_prm_fix (pa);
        dl_prm_fix (pb);
        return;
      }
      x -= v->b - v->a;

      v->p = pa;
      pa = v;

      *a = v;
      a = &v->r;
      v = v->r;
    }

  }
  assert (0);
}