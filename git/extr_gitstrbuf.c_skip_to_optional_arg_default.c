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
 int /*<<< orphan*/  skip_prefix (char const*,char const*,char const**) ; 

int skip_to_optional_arg_default(const char *str, const char *prefix,
				 const char **arg, const char *def)
{
	const char *p;

	if (!skip_prefix(str, prefix, &p))
		return 0;

	if (!*p) {
		if (arg)
			*arg = def;
		return 1;
	}

	if (*p != '=')
		return 0;

	if (arg)
		*arg = p + 1;
	return 1;
}