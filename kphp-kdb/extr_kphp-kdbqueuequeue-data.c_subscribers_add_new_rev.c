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
 TYPE_1__* get_subscribers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  treap_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  treap_cnt_rev ; 

int subscribers_add_new_rev (ll id, pli *a, int n) {
  //TODO: force?
  subscribers *s = get_subscribers (id, 0);
  if (s != NULL) {
    treap_cnt_rev += s->s.size;

    int i;
    for (i = 0; i < n; i++) {
      treap_add (&s->s, a[i].x, a[i].y, rand());
      //dbg ("add subscriber(lazy) %lld->%lld\n", a[i].x, id);
    }
    treap_cnt_rev -= s->s.size;
  }

  return 1;
}