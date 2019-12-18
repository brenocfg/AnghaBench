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
 scalar_t__ charset ; 
 char* getenv (char*) ; 
 int is_encoding_utf8 (scalar_t__) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ xstrdup (char const*) ; 

int is_utf8_locale(void)
{
#ifdef NO_GETTEXT
	if (!charset) {
		const char *env = getenv("LC_ALL");
		if (!env || !*env)
			env = getenv("LC_CTYPE");
		if (!env || !*env)
			env = getenv("LANG");
		if (!env)
			env = "";
		if (strchr(env, '.'))
			env = strchr(env, '.') + 1;
		charset = xstrdup(env);
	}
#endif
	return is_encoding_utf8(charset);
}