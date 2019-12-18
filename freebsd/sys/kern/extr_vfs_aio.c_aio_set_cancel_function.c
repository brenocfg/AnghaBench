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
struct kaioinfo {int dummy; } ;
struct kaiocb {TYPE_1__* userproc; } ;
typedef  int /*<<< orphan*/  aio_cancel_fn_t ;
struct TYPE_2__ {struct kaioinfo* p_aioinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int aio_set_cancel_function_locked (struct kaiocb*,int /*<<< orphan*/ *) ; 

bool
aio_set_cancel_function(struct kaiocb *job, aio_cancel_fn_t *func)
{
	struct kaioinfo *ki;
	bool ret;

	ki = job->userproc->p_aioinfo;
	AIO_LOCK(ki);
	ret = aio_set_cancel_function_locked(job, func);
	AIO_UNLOCK(ki);
	return (ret);
}