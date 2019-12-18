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
struct kqueue {int kq_state; int /*<<< orphan*/  kq_refcnt; } ;
struct file {scalar_t__ f_type; struct kqueue* f_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_KQUEUE ; 
 int EBADF ; 
 int KQ_CLOSING ; 
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 

__attribute__((used)) static int
kqueue_acquire(struct file *fp, struct kqueue **kqp)
{
	int error;
	struct kqueue *kq;

	error = 0;

	kq = fp->f_data;
	if (fp->f_type != DTYPE_KQUEUE || kq == NULL)
		return (EBADF);
	*kqp = kq;
	KQ_LOCK(kq);
	if ((kq->kq_state & KQ_CLOSING) == KQ_CLOSING) {
		KQ_UNLOCK(kq);
		return (EBADF);
	}
	kq->kq_refcnt++;
	KQ_UNLOCK(kq);

	return error;
}