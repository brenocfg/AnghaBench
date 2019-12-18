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
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static int match_placeholder_arg_value(const char *to_parse, const char *candidate,
				       const char **end, const char **valuestart,
				       size_t *valuelen)
{
	const char *p;

	if (!(skip_prefix(to_parse, candidate, &p)))
		return 0;
	if (valuestart) {
		if (*p == '=') {
			*valuestart = p + 1;
			*valuelen = strcspn(*valuestart, ",)");
			p = *valuestart + *valuelen;
		} else {
			if (*p != ',' && *p != ')')
				return 0;
			*valuestart = NULL;
			*valuelen = 0;
		}
	}
	if (*p == ',') {
		*end = p + 1;
		return 1;
	}
	if (*p == ')') {
		*end = p;
		return 1;
	}
	return 0;
}