#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kqueue {int /*<<< orphan*/  kq_count; int /*<<< orphan*/  kq_head; } ;
struct knote {int kn_status; struct kqueue* kn_kq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KN_QUEUED ; 
 int /*<<< orphan*/  KQ_OWNED (struct kqueue*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_tqe ; 
 int /*<<< orphan*/  kqueue_wakeup (struct kqueue*) ; 

__attribute__((used)) static void
knote_enqueue(struct knote *kn)
{
	struct kqueue *kq = kn->kn_kq;

	KQ_OWNED(kn->kn_kq);
	KASSERT((kn->kn_status & KN_QUEUED) == 0, ("knote already queued"));

	TAILQ_INSERT_TAIL(&kq->kq_head, kn, kn_tqe);
	kn->kn_status |= KN_QUEUED;
	kq->kq_count++;
	kqueue_wakeup(kq);
}