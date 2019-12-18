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
struct TYPE_4__ {int a; int b; struct TYPE_4__* r; } ;
typedef  TYPE_1__ perm_list ;
struct TYPE_5__ {int len; TYPE_1__* v; } ;
typedef  TYPE_2__ dl_perm_list ;

/* Variables and functions */

int dl_perm_list_conv_to_array (dl_perm_list *p, int *a, int n) {
  perm_list *st = p->v, *v = st->r;

  int ln = 0;

  while (v != st) {
    int x;
    for (x = v->a; x < v->b; x++) {
      if (n) {
        *a++ = x;
        n--;
        ln++;
      }
    }
    v = v->r;
  }
  return p->len;
}