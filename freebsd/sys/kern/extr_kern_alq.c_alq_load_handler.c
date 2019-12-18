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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALD_LOCK () ; 
 int /*<<< orphan*/  ALD_UNLOCK () ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  ald_mtx ; 
 int /*<<< orphan*/  ald_queues ; 
 int /*<<< orphan*/  ald_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ald_shutingdown ; 
 int /*<<< orphan*/  alq_eventhandler_tag ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 

__attribute__((used)) static int
alq_load_handler(module_t mod, int what, void *arg)
{
	int ret;
	
	ret = 0;

	switch (what) {
	case MOD_LOAD:
	case MOD_SHUTDOWN:
		break;

	case MOD_QUIESCE:
		ALD_LOCK();
		/* Only allow unload if there are no open queues. */
		if (LIST_FIRST(&ald_queues) == NULL) {
			ald_shutingdown = 1;
			ALD_UNLOCK();
			EVENTHANDLER_DEREGISTER(shutdown_pre_sync,
			    alq_eventhandler_tag);
			ald_shutdown(NULL, 0);
			mtx_destroy(&ald_mtx);
		} else {
			ALD_UNLOCK();
			ret = EBUSY;
		}
		break;

	case MOD_UNLOAD:
		/* If MOD_QUIESCE failed we must fail here too. */
		if (ald_shutingdown == 0)
			ret = EBUSY;
		break;

	default:
		ret = EINVAL;
		break;
	}

	return (ret);
}