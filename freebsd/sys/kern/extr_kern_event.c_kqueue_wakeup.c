#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct kqueue {int kq_state; int /*<<< orphan*/  kq_sigio; TYPE_1__ kq_sel; } ;

/* Variables and functions */
 int KQ_ASYNC ; 
 int /*<<< orphan*/  KQ_OWNED (struct kqueue*) ; 
 int KQ_SEL ; 
 int KQ_SLEEP ; 
 int /*<<< orphan*/  PSOCK ; 
 int /*<<< orphan*/  SEL_WAITING (TYPE_1__*) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  knlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqueue_schedtask (struct kqueue*) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct kqueue*) ; 

__attribute__((used)) static void
kqueue_wakeup(struct kqueue *kq)
{
	KQ_OWNED(kq);

	if ((kq->kq_state & KQ_SLEEP) == KQ_SLEEP) {
		kq->kq_state &= ~KQ_SLEEP;
		wakeup(kq);
	}
	if ((kq->kq_state & KQ_SEL) == KQ_SEL) {
		selwakeuppri(&kq->kq_sel, PSOCK);
		if (!SEL_WAITING(&kq->kq_sel))
			kq->kq_state &= ~KQ_SEL;
	}
	if (!knlist_empty(&kq->kq_sel.si_note))
		kqueue_schedtask(kq);
	if ((kq->kq_state & KQ_ASYNC) == KQ_ASYNC) {
		pgsigio(&kq->kq_sigio, SIGIO, 0);
	}
}