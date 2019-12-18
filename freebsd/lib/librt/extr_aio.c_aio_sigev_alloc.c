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
struct sigevent {int dummy; } ;
struct sigev_node {int /*<<< orphan*/  sn_dispatch; int /*<<< orphan*/  sn_id; } ;
typedef  int /*<<< orphan*/  sigev_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SI_ASYNCIO ; 
 struct sigev_node* __sigev_alloc (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __sigev_check_init () ; 
 int /*<<< orphan*/  __sigev_get_sigevent (struct sigev_node*,struct sigevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  __sigev_register (struct sigev_node*) ; 
 int /*<<< orphan*/  aio_dispatch ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
aio_sigev_alloc(sigev_id_t id, struct sigevent *sigevent,
    struct sigev_node **sn, struct sigevent *saved_ev)
{
	if (__sigev_check_init()) {
		/* This might be that thread library is not enabled. */
		errno = EINVAL;
		return (-1);
	}

	*sn = __sigev_alloc(SI_ASYNCIO, sigevent, NULL, 1);
	if (*sn == NULL) {
		errno = EAGAIN;
		return (-1);
	}
	
	*saved_ev = *sigevent;
	(*sn)->sn_id = id;
	__sigev_get_sigevent(*sn, sigevent, (*sn)->sn_id);
	(*sn)->sn_dispatch = aio_dispatch;

	__sigev_list_lock();
	__sigev_register(*sn);
	__sigev_list_unlock();

	return (0);
}