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
struct cc_algo {int (* mod_init ) () ;int /*<<< orphan*/  (* mod_destroy ) () ;} ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int cc_deregister_algo (struct cc_algo*) ; 
 int cc_register_algo (struct cc_algo*) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int
cc_modevent(module_t mod, int event_type, void *data)
{
	struct cc_algo *algo;
	int err;

	err = 0;
	algo = (struct cc_algo *)data;

	switch(event_type) {
	case MOD_LOAD:
		if (algo->mod_init != NULL)
			err = algo->mod_init();
		if (!err)
			err = cc_register_algo(algo);
		break;

	case MOD_QUIESCE:
	case MOD_SHUTDOWN:
	case MOD_UNLOAD:
		err = cc_deregister_algo(algo);
		if (!err && algo->mod_destroy != NULL)
			algo->mod_destroy();
		if (err == ENOENT)
			err = 0;
		break;

	default:
		err = EINVAL;
		break;
	}

	return (err);
}