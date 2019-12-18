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
struct parse_opt_ctx_t {scalar_t__ opt; int /*<<< orphan*/  prefix; } ;
struct option {int flags; int type; int (* ll_callback ) (struct parse_opt_ctx_t*,struct option const*,char const*,int const) ;int defval; int extra; scalar_t__ value; int /*<<< orphan*/  (* callback ) (struct option const*,char const*,int) ;} ;
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,...) ; 
#define  OPTION_BIT 139 
#define  OPTION_BITOP 138 
#define  OPTION_CALLBACK 137 
#define  OPTION_CMDMODE 136 
#define  OPTION_COUNTUP 135 
#define  OPTION_FILENAME 134 
#define  OPTION_INTEGER 133 
#define  OPTION_LOWLEVEL_CALLBACK 132 
#define  OPTION_MAGNITUDE 131 
#define  OPTION_NEGBIT 130 
#define  OPTION_SET_INT 129 
#define  OPTION_STRING 128 
 int OPT_SHORT ; 
 int OPT_UNSET ; 
 int PARSE_OPT_NOARG ; 
 int PARSE_OPT_NONEG ; 
 int PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_filename (int /*<<< orphan*/ ,char const**) ; 
 int get_arg (struct parse_opt_ctx_t*,struct option const*,int,char const**) ; 
 int /*<<< orphan*/  git_parse_ulong (char const*,scalar_t__) ; 
 int opt_command_mode_error (struct option const*,struct option const*,int) ; 
 int /*<<< orphan*/  optname (struct option const*,int) ; 
 int strtol (char const*,char**,int) ; 
 int stub1 (struct parse_opt_ctx_t*,struct option const*,char const*,int const) ; 
 int /*<<< orphan*/  stub2 (struct option const*,char const*,int) ; 
 int stub3 (struct parse_opt_ctx_t*,struct option const*,char const*,int) ; 

__attribute__((used)) static enum parse_opt_result get_value(struct parse_opt_ctx_t *p,
				       const struct option *opt,
				       const struct option *all_opts,
				       int flags)
{
	const char *s, *arg;
	const int unset = flags & OPT_UNSET;
	int err;

	if (unset && p->opt)
		return error(_("%s takes no value"), optname(opt, flags));
	if (unset && (opt->flags & PARSE_OPT_NONEG))
		return error(_("%s isn't available"), optname(opt, flags));
	if (!(flags & OPT_SHORT) && p->opt && (opt->flags & PARSE_OPT_NOARG))
		return error(_("%s takes no value"), optname(opt, flags));

	switch (opt->type) {
	case OPTION_LOWLEVEL_CALLBACK:
		return opt->ll_callback(p, opt, NULL, unset);

	case OPTION_BIT:
		if (unset)
			*(int *)opt->value &= ~opt->defval;
		else
			*(int *)opt->value |= opt->defval;
		return 0;

	case OPTION_NEGBIT:
		if (unset)
			*(int *)opt->value |= opt->defval;
		else
			*(int *)opt->value &= ~opt->defval;
		return 0;

	case OPTION_BITOP:
		if (unset)
			BUG("BITOP can't have unset form");
		*(int *)opt->value &= ~opt->extra;
		*(int *)opt->value |= opt->defval;
		return 0;

	case OPTION_COUNTUP:
		if (*(int *)opt->value < 0)
			*(int *)opt->value = 0;
		*(int *)opt->value = unset ? 0 : *(int *)opt->value + 1;
		return 0;

	case OPTION_SET_INT:
		*(int *)opt->value = unset ? 0 : opt->defval;
		return 0;

	case OPTION_CMDMODE:
		/*
		 * Giving the same mode option twice, although is unnecessary,
		 * is not a grave error, so let it pass.
		 */
		if (*(int *)opt->value && *(int *)opt->value != opt->defval)
			return opt_command_mode_error(opt, all_opts, flags);
		*(int *)opt->value = opt->defval;
		return 0;

	case OPTION_STRING:
		if (unset)
			*(const char **)opt->value = NULL;
		else if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			*(const char **)opt->value = (const char *)opt->defval;
		else
			return get_arg(p, opt, flags, (const char **)opt->value);
		return 0;

	case OPTION_FILENAME:
		err = 0;
		if (unset)
			*(const char **)opt->value = NULL;
		else if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			*(const char **)opt->value = (const char *)opt->defval;
		else
			err = get_arg(p, opt, flags, (const char **)opt->value);

		if (!err)
			fix_filename(p->prefix, (const char **)opt->value);
		return err;

	case OPTION_CALLBACK:
	{
		const char *p_arg = NULL;
		int p_unset;

		if (unset)
			p_unset = 1;
		else if (opt->flags & PARSE_OPT_NOARG)
			p_unset = 0;
		else if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			p_unset = 0;
		else if (get_arg(p, opt, flags, &arg))
			return -1;
		else {
			p_unset = 0;
			p_arg = arg;
		}
		if (opt->callback)
			return (*opt->callback)(opt, p_arg, p_unset) ? (-1) : 0;
		else
			return (*opt->ll_callback)(p, opt, p_arg, p_unset);
	}
	case OPTION_INTEGER:
		if (unset) {
			*(int *)opt->value = 0;
			return 0;
		}
		if (opt->flags & PARSE_OPT_OPTARG && !p->opt) {
			*(int *)opt->value = opt->defval;
			return 0;
		}
		if (get_arg(p, opt, flags, &arg))
			return -1;
		if (!*arg)
			return error(_("%s expects a numerical value"),
				     optname(opt, flags));
		*(int *)opt->value = strtol(arg, (char **)&s, 10);
		if (*s)
			return error(_("%s expects a numerical value"),
				     optname(opt, flags));
		return 0;

	case OPTION_MAGNITUDE:
		if (unset) {
			*(unsigned long *)opt->value = 0;
			return 0;
		}
		if (opt->flags & PARSE_OPT_OPTARG && !p->opt) {
			*(unsigned long *)opt->value = opt->defval;
			return 0;
		}
		if (get_arg(p, opt, flags, &arg))
			return -1;
		if (!git_parse_ulong(arg, opt->value))
			return error(_("%s expects a non-negative integer value"
				       " with an optional k/m/g suffix"),
				     optname(opt, flags));
		return 0;

	default:
		BUG("opt->type %d should not happen", opt->type);
	}
}