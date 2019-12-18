#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  treap ;
struct TYPE_4__ {int /*<<< orphan*/ * subs; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 int /*<<< orphan*/  clear_subscr (TYPE_1__*) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  queues_memory ; 

void queue_clear_subs (queue *q) {
  if (q != NULL && q->name != NULL && q->subs != NULL) {
    clear_subscr (q);

    queues_memory -= dl_get_memory_used();
    dl_free (q->subs, sizeof (treap));
    queues_memory += dl_get_memory_used();
    q->subs = NULL;
  }
}