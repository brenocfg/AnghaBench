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
struct kaiocb {int jobflags; int /*<<< orphan*/ * cancel_fn; TYPE_1__* userproc; } ;
typedef  int /*<<< orphan*/  aio_cancel_fn_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_aioinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KAIOCB_CANCELLED ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static bool
aio_set_cancel_function_locked(struct kaiocb *job, aio_cancel_fn_t *func)
{

	AIO_LOCK_ASSERT(job->userproc->p_aioinfo, MA_OWNED);
	if (job->jobflags & KAIOCB_CANCELLED)
		return (false);
	job->cancel_fn = func;
	return (true);
}