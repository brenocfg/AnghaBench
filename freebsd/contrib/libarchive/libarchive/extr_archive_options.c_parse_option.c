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
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *
parse_option(const char **s, const char **m, const char **o, const char **v)
{
	const char *end, *mod, *opt, *val;
	char *p;

	end = NULL;
	mod = NULL;
	opt = *s;
	val = "1";

	p = strchr(opt, ',');

	if (p != NULL) {
		*p = '\0';
		end = ((const char *)p) + 1;
	}

	if (0 == strlen(opt)) {
		*s = end;
		*m = NULL;
		*o = NULL;
		*v = NULL;
		return end;
	}

	p = strchr(opt, ':');
	if (p != NULL) {
		*p = '\0';
		mod = opt;
		opt = ++p;
	}

	p = strchr(opt, '=');
	if (p != NULL) {
		*p = '\0';
		val = ++p;
	} else if (opt[0] == '!') {
		++opt;
		val = NULL;
	}

	*s = end;
	*m = mod;
	*o = opt;
	*v = val;

	return end;
}