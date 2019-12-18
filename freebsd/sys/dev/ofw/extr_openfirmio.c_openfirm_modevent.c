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
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  OPENFIRM_MINOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  openfirm_cdevsw ; 
 int /*<<< orphan*/  openfirm_dev ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
openfirm_modevent(module_t mod, int type, void *data)
{

	switch(type) {
	case MOD_LOAD:
		if (bootverbose)
			printf("openfirm: <Open Firmware control device>\n");
		/*
		 * Allow only root access by default; this device may allow
		 * users to peek into firmware passwords, and likely to crash
		 * the machine on some boxen due to firmware quirks.
		 */
		openfirm_dev = make_dev(&openfirm_cdevsw, OPENFIRM_MINOR,
		    UID_ROOT, GID_WHEEL, 0600, "openfirm");
		return 0;

	case MOD_UNLOAD:
		destroy_dev(openfirm_dev);
		return 0;

	case MOD_SHUTDOWN:
		return 0;

	default:
		return EOPNOTSUPP;
	}
}