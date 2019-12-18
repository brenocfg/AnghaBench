#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbitmap {int dummy; } ;
struct kyber_ctx_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/ * rq_list; } ;
struct flush_kcq_data {size_t sched_domain; int /*<<< orphan*/  list; TYPE_1__* khd; } ;
struct TYPE_2__ {struct kyber_ctx_queue* kcqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_clear_bit (struct sbitmap*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool flush_busy_kcq(struct sbitmap *sb, unsigned int bitnr, void *data)
{
	struct flush_kcq_data *flush_data = data;
	struct kyber_ctx_queue *kcq = &flush_data->khd->kcqs[bitnr];

	spin_lock(&kcq->lock);
	list_splice_tail_init(&kcq->rq_list[flush_data->sched_domain],
			      flush_data->list);
	sbitmap_clear_bit(sb, bitnr);
	spin_unlock(&kcq->lock);

	return true;
}