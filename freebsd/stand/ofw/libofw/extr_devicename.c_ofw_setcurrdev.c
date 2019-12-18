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
struct ofw_devdesc {int dummy; } ;
struct env_var {int /*<<< orphan*/  ev_name; } ;

/* Variables and functions */
 int EV_NOHOOK ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ofw_devdesc*) ; 
 int ofw_parsedev (struct ofw_devdesc**,void const*,int /*<<< orphan*/ *) ; 

int
ofw_setcurrdev(struct env_var *ev, int flags, const void *value)
{
    struct ofw_devdesc	*ncurr;
    int			rv;

    if ((rv = ofw_parsedev(&ncurr, value, NULL)) != 0)
	return rv;

    free(ncurr);
    env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);
    return 0;
}