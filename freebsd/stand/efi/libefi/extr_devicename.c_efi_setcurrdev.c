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
struct devdesc {int dummy; } ;

/* Variables and functions */
 int EV_NOHOOK ; 
 int efi_parsedev (struct devdesc**,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct devdesc*) ; 

int
efi_setcurrdev(struct env_var *ev, int flags, const void *value)
{
	struct devdesc *ncurr;
	int rv;

	rv = efi_parsedev(&ncurr, value, NULL);
	if (rv != 0)
		return (rv);

	free(ncurr);
	env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);
	return (0);
}