#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_6__ {TYPE_3__ s; } ;
typedef  TYPE_1__ subscribers ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ pli ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 TYPE_1__* get_subscribers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  treap_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  treap_cnt_rev ; 

int subscribers_add_new (ll id, pli *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    subscribers *s = get_subscribers (a[i].x, 1);
//    dbg ("add subscriber %d->%d[%d] %p\n", id, a[i].x, a[i].y, s);

    if (s != NULL) {
      treap_cnt_rev += s->s.size;
      treap_add (&s->s, id, a[i].y, rand());
      treap_cnt_rev -= s->s.size;

      //dbg ("add subscriber %lld->%lld[%d] (treap_size = %d)\n", id, a[i].x, a[i].y, s->s.size);
    }
  }

  return 1;
}