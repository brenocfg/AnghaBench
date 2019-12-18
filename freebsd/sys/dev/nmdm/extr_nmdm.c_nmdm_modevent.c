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
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  nmdm_clone ; 
 int /*<<< orphan*/  nmdm_count ; 

__attribute__((used)) static int
nmdm_modevent(module_t mod, int type, void *data)
{
	static eventhandler_tag tag;

        switch(type) {
        case MOD_LOAD: 
		tag = EVENTHANDLER_REGISTER(dev_clone, nmdm_clone, 0, 1000);
		if (tag == NULL)
			return (ENOMEM);
		break;

	case MOD_SHUTDOWN:
		break;

	case MOD_UNLOAD:
		if (nmdm_count != 0)
			return (EBUSY);
		EVENTHANDLER_DEREGISTER(dev_clone, tag);
		break;

	default:
		return (EOPNOTSUPP);
	}

	return (0);
}