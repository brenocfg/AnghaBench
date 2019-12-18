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

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
getnewbasename(char **newbasename, int typedefp, const char *basename, const char *name)
{
    if (typedefp)
	*newbasename = strdup(name);
    else {
	if (name[0] == '*')
	    name++;
	if (asprintf(newbasename, "%s_%s", basename, name) < 0)
	    errx(1, "malloc");
    }
    if (*newbasename == NULL)
	err(1, "malloc");
}