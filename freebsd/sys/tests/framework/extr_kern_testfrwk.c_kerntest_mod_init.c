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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_2__ {int /*<<< orphan*/  kfrwk_testlist; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KTFRWK_LOCK () ; 
 int /*<<< orphan*/  KTFRWK_UNLOCK () ; 
#define  MOD_LOAD 130 
#define  MOD_QUIESCE 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int kerntest_frwk_fini () ; 
 int kerntest_frwk_init () ; 
 TYPE_1__ kfrwk ; 

__attribute__((used)) static int
kerntest_mod_init(module_t mod, int type, void *data)
{
	int err;

	switch (type) {
	case MOD_LOAD:
		err = kerntest_frwk_init();
		break;
	case MOD_QUIESCE:
		KTFRWK_LOCK();
		if (TAILQ_EMPTY(&kfrwk.kfrwk_testlist)) {
			err = 0;
		} else {
			err = EBUSY;
		}
		KTFRWK_UNLOCK();
		break;
	case MOD_UNLOAD:
		err = kerntest_frwk_fini();
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (err);
}