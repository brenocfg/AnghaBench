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
struct strbuf {char* buf; } ;
struct option {scalar_t__ type; scalar_t__ value; int defval; scalar_t__ short_name; scalar_t__ long_name; } ;
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 scalar_t__ OPTION_CMDMODE ; 
 scalar_t__ OPTION_END ; 
 int PARSE_OPT_ERROR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  optname (struct option const*,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static enum parse_opt_result opt_command_mode_error(
	const struct option *opt,
	const struct option *all_opts,
	int flags)
{
	const struct option *that;
	struct strbuf that_name = STRBUF_INIT;

	/*
	 * Find the other option that was used to set the variable
	 * already, and report that this is not compatible with it.
	 */
	for (that = all_opts; that->type != OPTION_END; that++) {
		if (that == opt ||
		    that->type != OPTION_CMDMODE ||
		    that->value != opt->value ||
		    that->defval != *(int *)opt->value)
			continue;

		if (that->long_name)
			strbuf_addf(&that_name, "--%s", that->long_name);
		else
			strbuf_addf(&that_name, "-%c", that->short_name);
		error(_("%s is incompatible with %s"),
		      optname(opt, flags), that_name.buf);
		strbuf_release(&that_name);
		return PARSE_OPT_ERROR;
	}
	return error(_("%s : incompatible with something else"),
		     optname(opt, flags));
}