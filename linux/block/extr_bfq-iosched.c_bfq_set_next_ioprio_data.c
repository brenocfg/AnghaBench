#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_6__ {int prio_changed; int /*<<< orphan*/  new_weight; } ;
struct bfq_queue {int new_ioprio; int new_ioprio_class; TYPE_3__ entity; struct bfq_data* bfqd; } ;
struct bfq_io_cq {int /*<<< orphan*/  ioprio; } ;
struct bfq_data {TYPE_2__* queue; } ;
struct TYPE_5__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IOPRIO_BE_NR ; 
#define  IOPRIO_CLASS_BE 131 
#define  IOPRIO_CLASS_IDLE 130 
#define  IOPRIO_CLASS_NONE 129 
#define  IOPRIO_CLASS_RT 128 
 int IOPRIO_PRIO_CLASS (int /*<<< orphan*/ ) ; 
 void* IOPRIO_PRIO_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_ioprio_to_weight (scalar_t__) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_crit (char*,scalar_t__) ; 
 int task_nice_ioclass (struct task_struct*) ; 
 int task_nice_ioprio (struct task_struct*) ; 

__attribute__((used)) static void
bfq_set_next_ioprio_data(struct bfq_queue *bfqq, struct bfq_io_cq *bic)
{
	struct task_struct *tsk = current;
	int ioprio_class;
	struct bfq_data *bfqd = bfqq->bfqd;

	if (!bfqd)
		return;

	ioprio_class = IOPRIO_PRIO_CLASS(bic->ioprio);
	switch (ioprio_class) {
	default:
		dev_err(bfqq->bfqd->queue->backing_dev_info->dev,
			"bfq: bad prio class %d\n", ioprio_class);
		/* fall through */
	case IOPRIO_CLASS_NONE:
		/*
		 * No prio set, inherit CPU scheduling settings.
		 */
		bfqq->new_ioprio = task_nice_ioprio(tsk);
		bfqq->new_ioprio_class = task_nice_ioclass(tsk);
		break;
	case IOPRIO_CLASS_RT:
		bfqq->new_ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
		bfqq->new_ioprio_class = IOPRIO_CLASS_RT;
		break;
	case IOPRIO_CLASS_BE:
		bfqq->new_ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
		bfqq->new_ioprio_class = IOPRIO_CLASS_BE;
		break;
	case IOPRIO_CLASS_IDLE:
		bfqq->new_ioprio_class = IOPRIO_CLASS_IDLE;
		bfqq->new_ioprio = 7;
		break;
	}

	if (bfqq->new_ioprio >= IOPRIO_BE_NR) {
		pr_crit("bfq_set_next_ioprio_data: new_ioprio %d\n",
			bfqq->new_ioprio);
		bfqq->new_ioprio = IOPRIO_BE_NR;
	}

	bfqq->entity.new_weight = bfq_ioprio_to_weight(bfqq->new_ioprio);
	bfqq->entity.prio_changed = 1;
}