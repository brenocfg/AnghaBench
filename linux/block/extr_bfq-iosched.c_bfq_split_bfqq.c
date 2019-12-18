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
struct bfq_queue {int /*<<< orphan*/  pid; int /*<<< orphan*/  bfqd; } ;
struct bfq_io_cq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_clear_bfqq_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_split_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*) ; 
 int /*<<< orphan*/  bfq_put_cooperator (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 
 int bfqq_process_refs (struct bfq_queue*) ; 
 int /*<<< orphan*/  bic_set_bfqq (struct bfq_io_cq*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* current ; 

__attribute__((used)) static struct bfq_queue *
bfq_split_bfqq(struct bfq_io_cq *bic, struct bfq_queue *bfqq)
{
	bfq_log_bfqq(bfqq->bfqd, bfqq, "splitting queue");

	if (bfqq_process_refs(bfqq) == 1) {
		bfqq->pid = current->pid;
		bfq_clear_bfqq_coop(bfqq);
		bfq_clear_bfqq_split_coop(bfqq);
		return bfqq;
	}

	bic_set_bfqq(bic, NULL, 1);

	bfq_put_cooperator(bfqq);

	bfq_put_queue(bfqq);
	return NULL;
}