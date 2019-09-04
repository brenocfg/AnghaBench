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
 int /*<<< orphan*/  LC_MESSAGES ; 
 char* getenv (char*) ; 
 char* setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *get_preferred_languages(void)
{
	const char *retval;

	retval = getenv("LANGUAGE");
	if (retval && *retval)
		return retval;

#ifndef NO_GETTEXT
	retval = setlocale(LC_MESSAGES, NULL);
	if (retval && *retval &&
		strcmp(retval, "C") &&
		strcmp(retval, "POSIX"))
		return retval;
#endif

	return NULL;
}