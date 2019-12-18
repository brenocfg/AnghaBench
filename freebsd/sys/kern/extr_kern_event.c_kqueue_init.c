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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct kqueue {int /*<<< orphan*/  kq_task; int /*<<< orphan*/  kq_lock; TYPE_1__ kq_sel; int /*<<< orphan*/  kq_head; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kqueue*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqueue_task ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
kqueue_init(struct kqueue *kq)
{

	mtx_init(&kq->kq_lock, "kqueue", NULL, MTX_DEF | MTX_DUPOK);
	TAILQ_INIT(&kq->kq_head);
	knlist_init_mtx(&kq->kq_sel.si_note, &kq->kq_lock);
	TASK_INIT(&kq->kq_task, 0, kqueue_task, kq);
}