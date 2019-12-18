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
 char* DEFAULT_LANG ; 
 char* getenv (char*) ; 
 char* lang_default ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static const char *
get_locale(void)
{
	const char *locale;

	if ((locale = getenv("LC_ALL")) == NULL &&
	    (locale = getenv("LC_CTYPE")) == NULL &&
	    (locale = getenv("LANG")) == NULL)
		locale = lang_default;

	/* Check for alias */
	if (!strcmp(locale, "C"))
		locale = DEFAULT_LANG;

	return locale;
}