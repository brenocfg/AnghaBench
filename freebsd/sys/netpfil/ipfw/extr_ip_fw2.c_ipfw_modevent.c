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
 int EOPNOTSUPP ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 

__attribute__((used)) static int
ipfw_modevent(module_t mod, int type, void *unused)
{
	int err = 0;

	switch (type) {
	case MOD_LOAD:
		/* Called once at module load or
	 	 * system boot if compiled in. */
		break;
	case MOD_QUIESCE:
		/* Called before unload. May veto unloading. */
		break;
	case MOD_UNLOAD:
		/* Called during unload. */
		break;
	case MOD_SHUTDOWN:
		/* Called during system shutdown. */
		break;
	default:
		err = EOPNOTSUPP;
		break;
	}
	return err;
}