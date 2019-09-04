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
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_7__ {TYPE_3__* q; int /*<<< orphan*/  id; TYPE_1__ s; } ;
typedef  TYPE_2__ subscribers ;
struct TYPE_8__ {int /*<<< orphan*/  subscr_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (TYPE_2__*,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  h_subscribers ; 
 int /*<<< orphan*/  hset_llp_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_fix (TYPE_3__*) ; 
 int /*<<< orphan*/  subscribers_cnt ; 
 int /*<<< orphan*/  subscribers_memory ; 

void free_subscribers (subscribers *s) {
  assert (s->s.size == 0);
  hset_llp_del (&h_subscribers, &s->id);
  subscribers_cnt--;

  if (s->q != NULL) {
    s->q->subscr_cnt--;
    queue_fix (s->q);
  }

  subscribers_memory -= dl_get_memory_used();
  dl_free (s, sizeof (subscribers));
  subscribers_memory += dl_get_memory_used();
}