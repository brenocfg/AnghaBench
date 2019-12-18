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
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 unsigned int LOGIN_SETPATH ; 
 unsigned int LOGIN_SETPRIORITY ; 
 unsigned int LOGIN_SETRESOURCES ; 
 unsigned int LOGIN_SETUMASK ; 
 int /*<<< orphan*/  login_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * login_getclassbyname (char const*,int /*<<< orphan*/ *) ; 
 int setusercontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int
setclasscontext(const char *classname, unsigned int flags)
{
    int		rc;
    login_cap_t *lc;

    lc = login_getclassbyname(classname, NULL);

    flags &= LOGIN_SETRESOURCES | LOGIN_SETPRIORITY |
	    LOGIN_SETUMASK | LOGIN_SETPATH;

    rc = lc ? setusercontext(lc, NULL, 0, flags) : -1;
    login_close(lc);
    return (rc);
}