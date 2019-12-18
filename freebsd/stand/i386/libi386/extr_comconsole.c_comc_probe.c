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
typedef  scalar_t__ uint32_t ;
struct console {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_name; } ;

/* Variables and functions */
 int COMSPEED ; 
 int /*<<< orphan*/  EV_VOLATILE ; 
 int comc_curspeed ; 
 int comc_getspeed () ; 
 scalar_t__ comc_parse_pcidev (char*) ; 
 int comc_parseint (char*) ; 
 int /*<<< orphan*/  comc_pcidev_handle (scalar_t__) ; 
 int /*<<< orphan*/  comc_pcidev_set ; 
 int comc_port ; 
 int /*<<< orphan*/  comc_port_set ; 
 int /*<<< orphan*/  comc_setup (int,int) ; 
 int /*<<< orphan*/  comc_speed_set ; 
 TYPE_1__ comconsole ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static void
comc_probe(struct console *cp)
{
	char intbuf[16];
	char *cons, *env;
	int speed, port;
	uint32_t locator;

	if (comc_curspeed == 0) {
		comc_curspeed = COMSPEED;
		/*
		 * Assume that the speed was set by an earlier boot loader if
		 * comconsole is already the preferred console.
		 */
		cons = getenv("console");
		if ((cons != NULL && strcmp(cons, comconsole.c_name) == 0) ||
		    getenv("boot_multicons") != NULL) {
			comc_curspeed = comc_getspeed();
		}

		env = getenv("comconsole_speed");
		if (env != NULL) {
			speed = comc_parseint(env);
			if (speed > 0)
				comc_curspeed = speed;
		}

		sprintf(intbuf, "%d", comc_curspeed);
		unsetenv("comconsole_speed");
		env_setenv("comconsole_speed", EV_VOLATILE, intbuf,
		    comc_speed_set, env_nounset);

		env = getenv("comconsole_port");
		if (env != NULL) {
			port = comc_parseint(env);
			if (port > 0)
				comc_port = port;
		}

		sprintf(intbuf, "%d", comc_port);
		unsetenv("comconsole_port");
		env_setenv("comconsole_port", EV_VOLATILE, intbuf,
		    comc_port_set, env_nounset);

		env = getenv("comconsole_pcidev");
		if (env != NULL) {
			locator = comc_parse_pcidev(env);
			if (locator != 0)
				comc_pcidev_handle(locator);
		}

		unsetenv("comconsole_pcidev");
		env_setenv("comconsole_pcidev", EV_VOLATILE, env,
		    comc_pcidev_set, env_nounset);
	}
	comc_setup(comc_curspeed, comc_port);
}