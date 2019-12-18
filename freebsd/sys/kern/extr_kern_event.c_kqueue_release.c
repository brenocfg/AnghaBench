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
struct kqueue {int kq_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_OWNED (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
kqueue_release(struct kqueue *kq, int locked)
{
	if (locked)
		KQ_OWNED(kq);
	else
		KQ_LOCK(kq);
	kq->kq_refcnt--;
	if (kq->kq_refcnt == 1)
		wakeup(&kq->kq_refcnt);
	if (!locked)
		KQ_UNLOCK(kq);
}