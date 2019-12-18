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
struct kaioinfo {int /*<<< orphan*/  kaio_syncready; } ;
struct kaiocb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct kaiocb* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_process_sync ; 
 int /*<<< orphan*/  aio_schedule (struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 

__attribute__((used)) static void
aio_schedule_fsync(void *context, int pending)
{
	struct kaioinfo *ki;
	struct kaiocb *job;

	ki = context;
	AIO_LOCK(ki);
	while (!TAILQ_EMPTY(&ki->kaio_syncready)) {
		job = TAILQ_FIRST(&ki->kaio_syncready);
		TAILQ_REMOVE(&ki->kaio_syncready, job, list);
		AIO_UNLOCK(ki);
		aio_schedule(job, aio_process_sync);
		AIO_LOCK(ki);
	}
	AIO_UNLOCK(ki);
}