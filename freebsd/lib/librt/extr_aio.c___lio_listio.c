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
struct sigevent {scalar_t__ sigev_notify; } ;
struct sigev_node {int dummy; } ;
struct aiocb {int dummy; } ;
typedef  int /*<<< orphan*/  sigev_id_t ;

/* Variables and functions */
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  __sigev_delete_node (struct sigev_node*) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int __sys_lio_listio (int,struct aiocb* const*,int,struct sigevent*) ; 
 int aio_sigev_alloc (int /*<<< orphan*/ ,struct sigevent*,struct sigev_node**,struct sigevent*) ; 
 int errno ; 

int
__lio_listio(int mode, struct aiocb * const list[], int nent,
    struct sigevent *sig)
{
	struct sigev_node *sn;
	struct sigevent saved_ev;
	int ret, err;

	if (sig == NULL || sig->sigev_notify != SIGEV_THREAD)
		return (__sys_lio_listio(mode, list, nent, sig));

	ret = aio_sigev_alloc((sigev_id_t)list, sig, &sn, &saved_ev);
	if (ret)
		return (ret);
	ret = __sys_lio_listio(mode, list, nent, sig);
	*sig = saved_ev;
	if (ret != 0) {
		err = errno;
		__sigev_list_lock();
		__sigev_delete_node(sn);
		__sigev_list_unlock();
		errno = err;
	}
	return (ret);
}