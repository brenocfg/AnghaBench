#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_7__ {int a; struct TYPE_7__* xl; struct TYPE_7__* xr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_prm_rev_merge (TYPE_1__**,TYPE_1__*,TYPE_1__*) ; 

dl_prm_ptr dl_prm_rev_del (dl_prm_ptr *v, int x) {
  //fprintf (stderr, "del %d\n", x);
  //_go_rev (*v, 0);
  while (*v != NULL) {
    //fprintf (stderr, "?%d\n", (*v)->a);
    if ((*v)->a  == x) {
      dl_prm_ptr t = *v;
      //fprintf (stderr, "found %d %d\n", (*v)->a, (*v)->b);
      dl_prm_rev_merge (v, t->xl, t->xr);

      return t;
    } else if ((*v)->a < x) {
      v = &(*v)->xr;
    } else if ((*v)->a > x) {
      v = &(*v)->xl;
    }
  }
  return NULL;
}