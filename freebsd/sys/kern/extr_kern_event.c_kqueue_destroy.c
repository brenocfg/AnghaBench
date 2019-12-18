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
struct kqueue {int /*<<< orphan*/  kq_sigio; int /*<<< orphan*/ * kq_knlist; int /*<<< orphan*/ * kq_knhash; int /*<<< orphan*/  kq_lock; TYPE_1__ kq_sel; int /*<<< orphan*/ * kq_fdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
kqueue_destroy(struct kqueue *kq)
{

	KASSERT(kq->kq_fdp == NULL,
	    ("kqueue still attached to a file descriptor"));
	seldrain(&kq->kq_sel);
	knlist_destroy(&kq->kq_sel.si_note);
	mtx_destroy(&kq->kq_lock);

	if (kq->kq_knhash != NULL)
		free(kq->kq_knhash, M_KQUEUE);
	if (kq->kq_knlist != NULL)
		free(kq->kq_knlist, M_KQUEUE);

	funsetown(&kq->kq_sigio);
}