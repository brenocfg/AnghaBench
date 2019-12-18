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
struct env_var {int /*<<< orphan*/  ev_name; } ;
struct TYPE_2__ {int c_flags; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int C_ACTIVEIN ; 
 int C_ACTIVEOUT ; 
 int EV_NOHOOK ; 
 scalar_t__ comc_locator ; 
 scalar_t__ comc_parse_pcidev (void const*) ; 
 int comc_pcidev_handle (scalar_t__) ; 
 TYPE_1__ comconsole ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
comc_pcidev_set(struct env_var *ev, int flags, const void *value)
{
	uint32_t locator;
	int error;

	if (value == NULL || (locator = comc_parse_pcidev(value)) <= 0) {
		printf("Invalid pcidev\n");
		return (CMD_ERROR);
	}
	if ((comconsole.c_flags & (C_ACTIVEIN | C_ACTIVEOUT)) != 0 &&
	    comc_locator != locator) {
		error = comc_pcidev_handle(locator);
		if (error != CMD_OK)
			return (error);
	}
	env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);
	return (CMD_OK);
}