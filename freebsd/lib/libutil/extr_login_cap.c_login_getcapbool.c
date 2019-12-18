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
 int /*<<< orphan*/ * cgetcap (int /*<<< orphan*/ *,char const*,char) ; 

int
login_getcapbool(login_cap_t *lc, const char *cap, int def)
{
    if (lc == NULL || lc->lc_cap == NULL)
	return def;
    return (cgetcap(lc->lc_cap, cap, ':') != NULL);
}