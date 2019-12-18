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
struct parse_opt_ctx_t {char** alias_groups; } ;
struct option {int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 scalar_t__ has_string (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int is_alias(struct parse_opt_ctx_t *ctx,
		    const struct option *one_opt,
		    const struct option *another_opt)
{
	const char **group;

	if (!ctx->alias_groups)
		return 0;

	if (!one_opt->long_name || !another_opt->long_name)
		return 0;

	for (group = ctx->alias_groups; *group; group += 3) {
		/* it and other are from the same family? */
		if (has_string(one_opt->long_name, group) &&
		    has_string(another_opt->long_name, group))
			return 1;
	}
	return 0;
}