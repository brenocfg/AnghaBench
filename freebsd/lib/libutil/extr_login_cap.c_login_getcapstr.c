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
struct TYPE_3__ {int /*<<< orphan*/ * lc_cap; } ;
typedef  TYPE_1__ login_cap_t ;

/* Variables and functions */
 int cgetstr (int /*<<< orphan*/ *,char const*,char**) ; 

const char *
login_getcapstr(login_cap_t *lc, const char *cap, const char *def, const char *error)
{
    char    *res;
    int	    ret;

    if (lc == NULL || cap == NULL || lc->lc_cap == NULL || *cap == '\0')
	return def;

    if ((ret = cgetstr(lc->lc_cap, cap, &res)) == -1)
	return def;
    return (ret >= 0) ? res : error;
}