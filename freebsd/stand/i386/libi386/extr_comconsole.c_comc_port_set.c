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
struct env_var {int /*<<< orphan*/  ev_name; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int EV_NOHOOK ; 
 int /*<<< orphan*/  comc_curspeed ; 
 int comc_parseint (void const*) ; 
 int comc_port ; 
 int /*<<< orphan*/  comc_setup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
comc_port_set(struct env_var *ev, int flags, const void *value)
{
	int port;

	if (value == NULL || (port = comc_parseint(value)) <= 0) {
		printf("Invalid port\n");
		return (CMD_ERROR);
	}

	if (comc_port != port)
		comc_setup(comc_curspeed, port);

	env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);

	return (CMD_OK);
}