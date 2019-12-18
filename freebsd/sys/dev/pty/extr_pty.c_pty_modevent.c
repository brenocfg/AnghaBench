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
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL_KLD ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ptmx_cdevsw ; 
 int /*<<< orphan*/  pty_clone ; 

__attribute__((used)) static int
pty_modevent(module_t mod, int type, void *data)
{

	switch(type) {
	case MOD_LOAD:
		EVENTHANDLER_REGISTER(dev_clone, pty_clone, 0, 1000);
		make_dev_credf(MAKEDEV_ETERNAL_KLD, &ptmx_cdevsw, 0, NULL,
		    UID_ROOT, GID_WHEEL, 0666, "ptmx");
		break;
	case MOD_SHUTDOWN:
		break;
	case MOD_UNLOAD:
		/* XXX: No unloading support yet. */
		return (EBUSY);
	default:
		return (EOPNOTSUPP);
	}

	return (0);
}