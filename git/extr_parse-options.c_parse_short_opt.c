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
struct parse_opt_ctx_t {scalar_t__* opt; } ;
struct option {scalar_t__ type; scalar_t__ short_name; int (* ll_callback ) (struct parse_opt_ctx_t*,struct option const*,char*,int /*<<< orphan*/ ) ;scalar_t__ (* callback ) (struct option const*,char*,int /*<<< orphan*/ ) ;} ;
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 scalar_t__ OPTION_NUMBER ; 
 int /*<<< orphan*/  OPT_SHORT ; 
 int PARSE_OPT_UNKNOWN ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_value (struct parse_opt_ctx_t*,struct option const*,struct option const*,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (scalar_t__) ; 
 scalar_t__ stub1 (struct option const*,char*,int /*<<< orphan*/ ) ; 
 int stub2 (struct parse_opt_ctx_t*,struct option const*,char*,int /*<<< orphan*/ ) ; 
 char* xmemdupz (scalar_t__*,size_t) ; 

__attribute__((used)) static enum parse_opt_result parse_short_opt(struct parse_opt_ctx_t *p,
					     const struct option *options)
{
	const struct option *all_opts = options;
	const struct option *numopt = NULL;

	for (; options->type != OPTION_END; options++) {
		if (options->short_name == *p->opt) {
			p->opt = p->opt[1] ? p->opt + 1 : NULL;
			return get_value(p, options, all_opts, OPT_SHORT);
		}

		/*
		 * Handle the numerical option later, explicit one-digit
		 * options take precedence over it.
		 */
		if (options->type == OPTION_NUMBER)
			numopt = options;
	}
	if (numopt && isdigit(*p->opt)) {
		size_t len = 1;
		char *arg;
		int rc;

		while (isdigit(p->opt[len]))
			len++;
		arg = xmemdupz(p->opt, len);
		p->opt = p->opt[len] ? p->opt + len : NULL;
		if (numopt->callback)
			rc = (*numopt->callback)(numopt, arg, 0) ? (-1) : 0;
		else
			rc = (*numopt->ll_callback)(p, numopt, arg, 0);
		free(arg);
		return rc;
	}
	return PARSE_OPT_UNKNOWN;
}