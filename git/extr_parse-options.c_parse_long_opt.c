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
struct parse_opt_ctx_t {char const** out; int flags; char const* opt; int /*<<< orphan*/  cpidx; } ;
struct option {scalar_t__ type; char* long_name; int defval; int flags; scalar_t__ value; } ;
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 scalar_t__ OPTION_ARGUMENT ; 
 scalar_t__ OPTION_END ; 
 int OPT_UNSET ; 
 int PARSE_OPT_DONE ; 
 int PARSE_OPT_HELP ; 
 int PARSE_OPT_KEEP_UNKNOWN ; 
 int PARSE_OPT_NONEG ; 
 int PARSE_OPT_UNKNOWN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (char*,int,char const*) ; 
 scalar_t__ disallow_abbreviated_options ; 
 int error (int /*<<< orphan*/ ,char const*,...) ; 
 int get_value (struct parse_opt_ctx_t*,struct option const*,struct option const*,int) ; 
 int /*<<< orphan*/  is_alias (struct parse_opt_ctx_t*,struct option const*,struct option const*) ; 
 int /*<<< orphan*/  optname (struct option const*,int) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char const*,char const**) ; 
 scalar_t__ starts_with (char const*,char const*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static enum parse_opt_result parse_long_opt(
	struct parse_opt_ctx_t *p, const char *arg,
	const struct option *options)
{
	const struct option *all_opts = options;
	const char *arg_end = strchrnul(arg, '=');
	const struct option *abbrev_option = NULL, *ambiguous_option = NULL;
	int abbrev_flags = 0, ambiguous_flags = 0;

	for (; options->type != OPTION_END; options++) {
		const char *rest, *long_name = options->long_name;
		int flags = 0, opt_flags = 0;

		if (!long_name)
			continue;

again:
		if (!skip_prefix(arg, long_name, &rest))
			rest = NULL;
		if (options->type == OPTION_ARGUMENT) {
			if (!rest)
				continue;
			if (*rest == '=')
				return error(_("%s takes no value"),
					     optname(options, flags));
			if (*rest)
				continue;
			if (options->value)
				*(int *)options->value = options->defval;
			p->out[p->cpidx++] = arg - 2;
			return PARSE_OPT_DONE;
		}
		if (!rest) {
			/* abbreviated? */
			if (!(p->flags & PARSE_OPT_KEEP_UNKNOWN) &&
			    !strncmp(long_name, arg, arg_end - arg)) {
is_abbreviated:
				if (abbrev_option &&
				    !is_alias(p, abbrev_option, options)) {
					/*
					 * If this is abbreviated, it is
					 * ambiguous. So when there is no
					 * exact match later, we need to
					 * error out.
					 */
					ambiguous_option = abbrev_option;
					ambiguous_flags = abbrev_flags;
				}
				if (!(flags & OPT_UNSET) && *arg_end)
					p->opt = arg_end + 1;
				abbrev_option = options;
				abbrev_flags = flags ^ opt_flags;
				continue;
			}
			/* negation allowed? */
			if (options->flags & PARSE_OPT_NONEG)
				continue;
			/* negated and abbreviated very much? */
			if (starts_with("no-", arg)) {
				flags |= OPT_UNSET;
				goto is_abbreviated;
			}
			/* negated? */
			if (!starts_with(arg, "no-")) {
				if (starts_with(long_name, "no-")) {
					long_name += 3;
					opt_flags |= OPT_UNSET;
					goto again;
				}
				continue;
			}
			flags |= OPT_UNSET;
			if (!skip_prefix(arg + 3, long_name, &rest)) {
				/* abbreviated and negated? */
				if (starts_with(long_name, arg + 3))
					goto is_abbreviated;
				else
					continue;
			}
		}
		if (*rest) {
			if (*rest != '=')
				continue;
			p->opt = rest + 1;
		}
		return get_value(p, options, all_opts, flags ^ opt_flags);
	}

	if (disallow_abbreviated_options && (ambiguous_option || abbrev_option))
		die("disallowed abbreviated or ambiguous option '%.*s'",
		    (int)(arg_end - arg), arg);

	if (ambiguous_option) {
		error(_("ambiguous option: %s "
			"(could be --%s%s or --%s%s)"),
			arg,
			(ambiguous_flags & OPT_UNSET) ?  "no-" : "",
			ambiguous_option->long_name,
			(abbrev_flags & OPT_UNSET) ?  "no-" : "",
			abbrev_option->long_name);
		return PARSE_OPT_HELP;
	}
	if (abbrev_option)
		return get_value(p, abbrev_option, all_opts, abbrev_flags);
	return PARSE_OPT_UNKNOWN;
}