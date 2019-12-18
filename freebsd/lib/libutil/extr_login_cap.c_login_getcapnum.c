#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rlim_t ;
struct TYPE_3__ {int /*<<< orphan*/  lc_class; int /*<<< orphan*/ * lc_cap; } ;
typedef  TYPE_1__ login_cap_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int cgetnum (int /*<<< orphan*/ *,char const*,long*) ; 
 int cgetstr (int /*<<< orphan*/ *,char const*,char**) ; 
 scalar_t__ errno ; 
 scalar_t__ isinfinite (char*) ; 
 int /*<<< orphan*/  strtoq (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char*) ; 

rlim_t
login_getcapnum(login_cap_t *lc, const char *cap, rlim_t def, rlim_t error)
{
    char    *ep, *res;
    int	    r;
    rlim_t  val;

    if (lc == NULL || lc->lc_cap == NULL)
	return def;

    /*
     * For BSDI compatibility, try for the tag=<val> first
     */
    if ((r = cgetstr(lc->lc_cap, cap, &res)) == -1) {
	long	lval;
	/* string capability not present, so try for tag#<val> as numeric */
	if ((r = cgetnum(lc->lc_cap, cap, &lval)) == -1)
	    return def; /* Not there, so return default */
	else if (r >= 0)
	    return (rlim_t)lval;
    }

    if (r < 0) {
	errno = ERANGE;
	return error;
    }

    if (isinfinite(res))
	return RLIM_INFINITY;

    errno = 0;
    val = strtoq(res, &ep, 0);
    if (ep == NULL || ep == res || errno != 0) {
	syslog(LOG_WARNING, "login_getcapnum: class '%s' bad value %s=%s",
	       lc->lc_class, cap, res);
	errno = ERANGE;
	return error;
    }

    return val;
}