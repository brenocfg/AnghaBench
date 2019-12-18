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
struct disk_devdesc {int dummy; } ;

/* Variables and functions */
 int EV_NOHOOK ; 
 int beri_arch_parsedev (struct disk_devdesc**,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct disk_devdesc*) ; 

int
beri_arch_setcurrdev(struct env_var *ev, int flags, const void *value)
{
    struct disk_devdesc	*ncurr;
    int			rv;

    if ((rv = beri_arch_parsedev(&ncurr, value, NULL)) != 0)
	return(rv);
    free(ncurr);
    env_setenv(ev->ev_name, flags | EV_NOHOOK, value, NULL, NULL);
    return(0);
}