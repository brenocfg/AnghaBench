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
struct kaioinfo {int /*<<< orphan*/  kaio_syncqueue; } ;
struct kaiocb {TYPE_1__* userproc; } ;
struct TYPE_2__ {struct kaioinfo* p_aioinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_cancel (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_cancel_cleared (struct kaiocb*) ; 
 int /*<<< orphan*/  list ; 

__attribute__((used)) static void
aio_cancel_sync(struct kaiocb *job)
{
	struct kaioinfo *ki;

	ki = job->userproc->p_aioinfo;
	AIO_LOCK(ki);
	if (!aio_cancel_cleared(job))
		TAILQ_REMOVE(&ki->kaio_syncqueue, job, list);
	AIO_UNLOCK(ki);
	aio_cancel(job);
}