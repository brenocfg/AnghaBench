#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  size; TYPE_2__* root; } ;
typedef  TYPE_1__ wkey_set ;
typedef  TYPE_2__* wkey_ptr ;
struct TYPE_11__ {int y; int x; struct TYPE_11__* r; struct TYPE_11__* l; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_2__ wkey ;
typedef  int /*<<< orphan*/  watchcat ;

/* Variables and functions */
 TYPE_2__* alloc_wkey () ; 
 int /*<<< orphan*/  trp_split (TYPE_2__*,int,TYPE_2__**,TYPE_2__**) ; 

wkey *trp_add (wkey_set *tr, int x, int y, watchcat *p) {
  wkey_ptr *v = &tr->root;

  while (*v != NULL && ((*v)->y >= y)) {
    if ((*v)->x == x) {
      return *v;
    } else if ((*v)->x > x) {
      v = &(*v)->r;
    } else if ((*v)->x < x) {
      v = &(*v)->l;
    }
  }
  wkey_ptr vv = *v;

  while (vv != NULL) {
    if (vv->x == x) {
      return vv;
    } else if (vv->x > x) {
      vv = vv->r;
    } else if (vv->x < x) {
      vv = vv->l;
    }
  }
  wkey_ptr u = alloc_wkey();
  //fprintf (stderr, "watchcat allocated (%d %d %p)\n", x, y, p);
  tr->size++;
  u->x = x;
  u->y = y;
  u->parent = p;
  trp_split (*v, x, &u->l, &u->r);
  *v = u;

  return u;
}