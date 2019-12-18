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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct kqueue {int /*<<< orphan*/  kq_state; int /*<<< orphan*/  kq_sel; scalar_t__ kq_count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_SEL ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 scalar_t__ SEL_WAITING (int /*<<< orphan*/ *) ; 
 int kqueue_acquire (struct file*,struct kqueue**) ; 
 int /*<<< orphan*/  kqueue_release (struct kqueue*,int) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kqueue_poll(struct file *fp, int events, struct ucred *active_cred,
	struct thread *td)
{
	struct kqueue *kq;
	int revents = 0;
	int error;

	if ((error = kqueue_acquire(fp, &kq)))
		return POLLERR;

	KQ_LOCK(kq);
	if (events & (POLLIN | POLLRDNORM)) {
		if (kq->kq_count) {
			revents |= events & (POLLIN | POLLRDNORM);
		} else {
			selrecord(td, &kq->kq_sel);
			if (SEL_WAITING(&kq->kq_sel))
				kq->kq_state |= KQ_SEL;
		}
	}
	kqueue_release(kq, 1);
	KQ_UNLOCK(kq);
	return (revents);
}