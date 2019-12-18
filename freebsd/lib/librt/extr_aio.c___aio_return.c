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
struct TYPE_2__ {scalar_t__ sigev_notify; } ;
struct aiocb {TYPE_1__ aio_sigevent; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sigev_id_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SI_ASYNCIO ; 
 int /*<<< orphan*/  __sigev_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 scalar_t__ __sys_aio_error (struct aiocb*) ; 
 int __sys_aio_return (struct aiocb*) ; 
 int /*<<< orphan*/  errno ; 

ssize_t
__aio_return(struct aiocb *iocb)
{

	if (iocb->aio_sigevent.sigev_notify == SIGEV_THREAD) {
		if (__sys_aio_error(iocb) == EINPROGRESS) {
			/*
			 * Fail with EINVAL to match the semantics of
			 * __sys_aio_return() for an in-progress
			 * request.
			 */
			errno = EINVAL;
			return (-1);
		}
		__sigev_list_lock();
		__sigev_delete(SI_ASYNCIO, (sigev_id_t)iocb);
		__sigev_list_unlock();
	}

	return __sys_aio_return(iocb);
}