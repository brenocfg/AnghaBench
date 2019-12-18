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
 char const** arrayize (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* login_getcapstr (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char **
login_getcaplist(login_cap_t *lc, const char *cap, const char *chars)
{
    const char *lstring;

    if (chars == NULL)
	chars = ", \t";
    if ((lstring = login_getcapstr(lc, cap, NULL, NULL)) != NULL)
	return arrayize(lstring, chars, NULL);
    return NULL;
}