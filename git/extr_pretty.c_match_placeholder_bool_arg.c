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
 int /*<<< orphan*/  free (char*) ; 
 int git_parse_maybe_bool (char*) ; 
 int /*<<< orphan*/  match_placeholder_arg_value (char const*,char const*,char const**,char const**,size_t*) ; 
 char* xstrndup (char const*,size_t) ; 

__attribute__((used)) static int match_placeholder_bool_arg(const char *to_parse, const char *candidate,
				      const char **end, int *val)
{
	const char *argval;
	char *strval;
	size_t arglen;
	int v;

	if (!match_placeholder_arg_value(to_parse, candidate, end, &argval, &arglen))
		return 0;

	if (!argval) {
		*val = 1;
		return 1;
	}

	strval = xstrndup(argval, arglen);
	v = git_parse_maybe_bool(strval);
	free(strval);

	if (v == -1)
		return 0;

	*val = v;

	return 1;
}