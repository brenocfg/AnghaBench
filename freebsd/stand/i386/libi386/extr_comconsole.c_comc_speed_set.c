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
 int comc_curspeed ; 
 int comc_parseint (void const*) ; 
 int /*<<< orphan*/  comc_port ; 
 int /*<<< orphan*/  comc_setup (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
comc_speed_set(struct env_var *ev, int flags, const void *value)
{
	int speed;

	if (value == NULL || (speed = comc_parseint(value)) <= 0) {
		printf("Invalid speed\n");
		return (CMD_ERROR);
	}

	if (comc_curspeed != speed)
		comc_setup(speed, comc_port);

	env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);

	return (CMD_OK);
}