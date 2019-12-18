#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct sbq_wait_state {TYPE_2__ wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct sbq_wait {TYPE_1__ wait; } ;
struct sbitmap_queue {int dummy; } ;
struct kyber_queue_data {struct sbitmap_queue* domain_tokens; } ;
struct kyber_hctx_data {unsigned int cur_domain; struct sbq_wait_state** domain_ws; int /*<<< orphan*/ * wait_index; struct sbq_wait* domain_wait; } ;
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int __sbitmap_queue_get (struct sbitmap_queue*) ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_add_wait_queue (struct sbitmap_queue*,struct sbq_wait_state*,struct sbq_wait*) ; 
 int /*<<< orphan*/  sbitmap_del_wait_queue (struct sbq_wait*) ; 
 struct sbq_wait_state* sbq_wait_ptr (struct sbitmap_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kyber_get_domain_token(struct kyber_queue_data *kqd,
				  struct kyber_hctx_data *khd,
				  struct blk_mq_hw_ctx *hctx)
{
	unsigned int sched_domain = khd->cur_domain;
	struct sbitmap_queue *domain_tokens = &kqd->domain_tokens[sched_domain];
	struct sbq_wait *wait = &khd->domain_wait[sched_domain];
	struct sbq_wait_state *ws;
	int nr;

	nr = __sbitmap_queue_get(domain_tokens);

	/*
	 * If we failed to get a domain token, make sure the hardware queue is
	 * run when one becomes available. Note that this is serialized on
	 * khd->lock, but we still need to be careful about the waker.
	 */
	if (nr < 0 && list_empty_careful(&wait->wait.entry)) {
		ws = sbq_wait_ptr(domain_tokens,
				  &khd->wait_index[sched_domain]);
		khd->domain_ws[sched_domain] = ws;
		sbitmap_add_wait_queue(domain_tokens, ws, wait);

		/*
		 * Try again in case a token was freed before we got on the wait
		 * queue.
		 */
		nr = __sbitmap_queue_get(domain_tokens);
	}

	/*
	 * If we got a token while we were on the wait queue, remove ourselves
	 * from the wait queue to ensure that all wake ups make forward
	 * progress. It's possible that the waker already deleted the entry
	 * between the !list_empty_careful() check and us grabbing the lock, but
	 * list_del_init() is okay with that.
	 */
	if (nr >= 0 && !list_empty_careful(&wait->wait.entry)) {
		ws = khd->domain_ws[sched_domain];
		spin_lock_irq(&ws->wait.lock);
		sbitmap_del_wait_queue(wait);
		spin_unlock_irq(&ws->wait.lock);
	}

	return nr;
}