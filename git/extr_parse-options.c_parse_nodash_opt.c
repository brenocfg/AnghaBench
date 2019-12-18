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
struct parse_opt_ctx_t {int dummy; } ;
struct option {scalar_t__ type; int flags; char const short_name; } ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 int /*<<< orphan*/  OPT_SHORT ; 
 int PARSE_OPT_NODASH ; 
 int get_value (struct parse_opt_ctx_t*,struct option const*,struct option const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_nodash_opt(struct parse_opt_ctx_t *p, const char *arg,
			    const struct option *options)
{
	const struct option *all_opts = options;

	for (; options->type != OPTION_END; options++) {
		if (!(options->flags & PARSE_OPT_NODASH))
			continue;
		if (options->short_name == arg[0] && arg[1] == '\0')
			return get_value(p, options, all_opts, OPT_SHORT);
	}
	return -2;
}