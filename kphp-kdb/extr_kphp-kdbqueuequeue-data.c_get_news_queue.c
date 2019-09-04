#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  treap ;
struct TYPE_6__ {scalar_t__ keys_cnt; int /*<<< orphan*/ * subs; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/ * dl_malloc (int) ; 
 int /*<<< orphan*/  get_news_s (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_queue (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* get_queue_by_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queues_memory ; 
 int /*<<< orphan*/  treap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_news (TYPE_1__*) ; 

queue *get_news_queue (ll id, int force) {
//  dbg ("get news_queue %lld %d\n", id, force);
  queue *q;

  if (!IS_UID (id)) {
    q = get_queue_by_alias (id);
    if (q == NULL) {
      return NULL;
    }
  } else {
    q = get_queue (get_news_s (id), force);
  }
  if (q != NULL) {
    //IMPORTANT: we mustn't add something to q->subs if nobody listens to it i.e. if keys_cnt == 0
    if (q->keys_cnt == 0 && !force) {
      return NULL;
    }
    if (q->subs == NULL) {
      //TODO
      queues_memory -= dl_get_memory_used();
      q->subs = dl_malloc (sizeof (treap));
      queues_memory += dl_get_memory_used();
      treap_init (q->subs);
    }

    if (force) {
      update_news (q);
    }
  }

  return q;
}