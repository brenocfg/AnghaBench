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
struct repository {int dummy; } ;
struct grep_opt {char const* prefix; int /*<<< orphan*/ * colors; int /*<<< orphan*/  output; int /*<<< orphan*/  relative; int /*<<< orphan*/  pathname; int /*<<< orphan*/  max_depth; int /*<<< orphan*/  columnnum; int /*<<< orphan*/  linenum; int /*<<< orphan*/  pattern_type_option; int /*<<< orphan*/  extended_regexp_option; int /*<<< orphan*/  color; int /*<<< orphan*/  only_matching; int /*<<< orphan*/  header_list; int /*<<< orphan*/ * header_tail; int /*<<< orphan*/  pattern_list; int /*<<< orphan*/ * pattern_tail; int /*<<< orphan*/  prefix_length; struct repository* repo; } ;

/* Variables and functions */
 int NR_GREP_COLORS ; 
 int /*<<< orphan*/  color_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct grep_opt grep_defaults ; 
 int /*<<< orphan*/  memset (struct grep_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void grep_init(struct grep_opt *opt, struct repository *repo, const char *prefix)
{
	struct grep_opt *def = &grep_defaults;
	int i;

	memset(opt, 0, sizeof(*opt));
	opt->repo = repo;
	opt->prefix = prefix;
	opt->prefix_length = (prefix && *prefix) ? strlen(prefix) : 0;
	opt->pattern_tail = &opt->pattern_list;
	opt->header_tail = &opt->header_list;

	opt->only_matching = def->only_matching;
	opt->color = def->color;
	opt->extended_regexp_option = def->extended_regexp_option;
	opt->pattern_type_option = def->pattern_type_option;
	opt->linenum = def->linenum;
	opt->columnnum = def->columnnum;
	opt->max_depth = def->max_depth;
	opt->pathname = def->pathname;
	opt->relative = def->relative;
	opt->output = def->output;

	for (i = 0; i < NR_GREP_COLORS; i++)
		color_set(opt->colors[i], def->colors[i]);
}