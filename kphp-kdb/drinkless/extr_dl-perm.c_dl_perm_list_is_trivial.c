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
struct TYPE_5__ {scalar_t__ n; scalar_t__ len; TYPE_1__* v; } ;
typedef  TYPE_2__ dl_perm_list ;
struct TYPE_4__ {struct TYPE_4__* r; } ;

/* Variables and functions */

int dl_perm_list_is_trivial (dl_perm_list *p) {
  return p->n == p->len && (p->v->r == p->v || p->v->r->r == p->v);
}