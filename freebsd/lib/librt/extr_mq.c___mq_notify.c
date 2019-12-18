#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  struct sigevent {scalar_t__ sigev_notify; } const sigevent ;
struct sigev_node {int /*<<< orphan*/  sn_gen; int /*<<< orphan*/  sn_dispatch; int /*<<< orphan*/  sn_id; } ;
typedef  TYPE_1__* mqd_t ;
struct TYPE_3__ {int /*<<< orphan*/  oshandle; struct sigev_node* node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SI_MESGQ ; 
 struct sigev_node* __sigev_alloc (int /*<<< orphan*/ ,struct sigevent const*,struct sigev_node*,int) ; 
 scalar_t__ __sigev_check_init () ; 
 int /*<<< orphan*/  __sigev_delete_node (struct sigev_node*) ; 
 int /*<<< orphan*/  __sigev_get_sigevent (struct sigev_node*,struct sigevent const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  __sigev_register (struct sigev_node*) ; 
 int __sys_kmq_notify (int /*<<< orphan*/ ,struct sigevent const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mq_dispatch ; 

int
__mq_notify(mqd_t mqd, const struct sigevent *evp)
{
	struct sigevent ev;
	struct sigev_node *sn;
	int ret;

	if (evp == NULL || evp->sigev_notify != SIGEV_THREAD) {
		if (mqd->node != NULL) {
			__sigev_list_lock();
			__sigev_delete_node(mqd->node);
			mqd->node = NULL;
			__sigev_list_unlock();
		}
		return __sys_kmq_notify(mqd->oshandle, evp);
	}

	if (__sigev_check_init()) {
		/*
		 * Thread library is not enabled.
		 */
		errno = EINVAL;
		return (-1);
	}

	sn = __sigev_alloc(SI_MESGQ, evp, mqd->node, 1);
	if (sn == NULL) {
		errno = EAGAIN;
		return (-1);
	}

	sn->sn_id = mqd->oshandle;
	sn->sn_dispatch = mq_dispatch;
	__sigev_get_sigevent(sn, &ev, sn->sn_gen);
	__sigev_list_lock();
	if (mqd->node != NULL)
		__sigev_delete_node(mqd->node);
	mqd->node = sn;
	__sigev_register(sn);
	ret = __sys_kmq_notify(mqd->oshandle, &ev);
	__sigev_list_unlock();
	return (ret);
}