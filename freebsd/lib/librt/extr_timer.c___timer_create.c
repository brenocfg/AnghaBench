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
typedef  struct __timer* timer_t ;
struct sigevent {scalar_t__ sigev_notify; } ;
struct sigev_node {int /*<<< orphan*/  sn_id; int /*<<< orphan*/  sn_dispatch; int /*<<< orphan*/  sn_flags; int /*<<< orphan*/  sn_gen; } ;
struct __timer {struct sigev_node* node; int /*<<< orphan*/  oshandle; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SI_TIMER ; 
 int /*<<< orphan*/  SNF_SYNC ; 
 struct sigev_node* __sigev_alloc (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ __sigev_check_init () ; 
 int /*<<< orphan*/  __sigev_free (struct sigev_node*) ; 
 int /*<<< orphan*/  __sigev_get_sigevent (struct sigev_node*,struct sigevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  __sigev_register (struct sigev_node*) ; 
 int __sys_ktimer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct __timer*) ; 
 struct __timer* malloc (int) ; 
 int /*<<< orphan*/  timer_dispatch ; 

int
__timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid)
{
	struct __timer *timer;
	struct sigevent ev;
	struct sigev_node *sn;
	int ret, err;

	timer = malloc(sizeof(struct __timer));
	if (timer == NULL)
		return (-1);

	if (evp == NULL || evp->sigev_notify != SIGEV_THREAD) {
		ret = __sys_ktimer_create(clockid, evp, &timer->oshandle);
		if (ret == -1) {
			err = errno;
			free(timer);
			errno = err;
			return (ret);
		}
		timer->node = NULL;
		*timerid = timer;
		return (0);
	}

	if (__sigev_check_init()) {
		free(timer);
		errno = EINVAL;
		return (-1);
	}

	sn = __sigev_alloc(SI_TIMER, evp, NULL, 0);
	if (sn == NULL) {
		free(timer);
		errno = EAGAIN;
		return (-1);
	}

	__sigev_get_sigevent(sn, &ev, sn->sn_gen);
	ret = __sys_ktimer_create(clockid, &ev, &timer->oshandle);
	if (ret != 0) {
		err = errno;
		__sigev_free(sn);
		free(timer);
		errno = err;
		return (-1);
	}
	sn->sn_flags |= SNF_SYNC;
	sn->sn_dispatch = timer_dispatch;
	sn->sn_id = timer->oshandle;
	timer->node = sn;
	__sigev_list_lock();
	__sigev_register(sn);
	__sigev_list_unlock();
	*timerid = timer;
	return (0);
}