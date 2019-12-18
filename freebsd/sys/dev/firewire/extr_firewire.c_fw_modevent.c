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
typedef  int /*<<< orphan*/ * eventhandler_tag ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  fwdev_clone ; 

__attribute__((used)) static int
fw_modevent(module_t mode, int type, void *data)
{
	int err = 0;
	static eventhandler_tag fwdev_ehtag = NULL;

	switch (type) {
	case MOD_LOAD:
		fwdev_ehtag = EVENTHANDLER_REGISTER(dev_clone,
		    fwdev_clone, 0, 1000);
		break;
	case MOD_UNLOAD:
		if (fwdev_ehtag != NULL)
			EVENTHANDLER_DEREGISTER(dev_clone, fwdev_ehtag);
		break;
	case MOD_SHUTDOWN:
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (err);
}