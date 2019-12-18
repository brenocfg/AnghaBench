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
struct ref_sorting {int ignore_case; } ;
struct ref_format {char* format; int /*<<< orphan*/  quote_style; int /*<<< orphan*/  use_color; } ;
struct ref_filter {int ignore_case; char const** name_patterns; int match_as_path; int nr; int /*<<< orphan*/ * items; int /*<<< orphan*/  no_commit; int /*<<< orphan*/  with_commit; int /*<<< orphan*/  points_at; } ;
struct ref_array {int ignore_case; char const** name_patterns; int match_as_path; int nr; int /*<<< orphan*/ * items; int /*<<< orphan*/  no_commit; int /*<<< orphan*/  with_commit; int /*<<< orphan*/  points_at; } ;
struct option {int dummy; } ;
typedef  int /*<<< orphan*/  filter ;
typedef  int /*<<< orphan*/  array ;

/* Variables and functions */
 int FILTER_REFS_ALL ; 
 int FILTER_REFS_INCLUDE_BROKEN ; 
 scalar_t__ HAS_MULTI_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BIT (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_CALLBACK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_CONTAINS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_GROUP (char*) ; 
 struct option OPT_INTEGER (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_MERGED (struct ref_filter*,int /*<<< orphan*/ ) ; 
 struct option OPT_NO_CONTAINS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_NO_MERGED (struct ref_filter*,int /*<<< orphan*/ ) ; 
 struct option OPT_REF_SORT (struct ref_sorting**) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__COLOR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUOTE_PERL ; 
 int /*<<< orphan*/  QUOTE_PYTHON ; 
 int /*<<< orphan*/  QUOTE_SHELL ; 
 int /*<<< orphan*/  QUOTE_TCL ; 
 struct ref_format REF_FORMAT_INIT ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  filter_refs (struct ref_filter*,struct ref_filter*,int) ; 
 int /*<<< orphan*/  for_each_ref_usage ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  memset (struct ref_filter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_opt_object_name ; 
 int /*<<< orphan*/  parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_array_clear (struct ref_filter*) ; 
 int /*<<< orphan*/  ref_array_sort (struct ref_sorting*,struct ref_filter*) ; 
 struct ref_sorting* ref_default_sorting () ; 
 int /*<<< orphan*/  show_ref_array_item (int /*<<< orphan*/ ,struct ref_format*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 scalar_t__ verify_ref_format (struct ref_format*) ; 

int cmd_for_each_ref(int argc, const char **argv, const char *prefix)
{
	int i;
	struct ref_sorting *sorting = NULL, **sorting_tail = &sorting;
	int maxcount = 0, icase = 0;
	struct ref_array array;
	struct ref_filter filter;
	struct ref_format format = REF_FORMAT_INIT;

	struct option opts[] = {
		OPT_BIT('s', "shell", &format.quote_style,
			N_("quote placeholders suitably for shells"), QUOTE_SHELL),
		OPT_BIT('p', "perl",  &format.quote_style,
			N_("quote placeholders suitably for perl"), QUOTE_PERL),
		OPT_BIT(0 , "python", &format.quote_style,
			N_("quote placeholders suitably for python"), QUOTE_PYTHON),
		OPT_BIT(0 , "tcl",  &format.quote_style,
			N_("quote placeholders suitably for Tcl"), QUOTE_TCL),

		OPT_GROUP(""),
		OPT_INTEGER( 0 , "count", &maxcount, N_("show only <n> matched refs")),
		OPT_STRING(  0 , "format", &format.format, N_("format"), N_("format to use for the output")),
		OPT__COLOR(&format.use_color, N_("respect format colors")),
		OPT_REF_SORT(sorting_tail),
		OPT_CALLBACK(0, "points-at", &filter.points_at,
			     N_("object"), N_("print only refs which points at the given object"),
			     parse_opt_object_name),
		OPT_MERGED(&filter, N_("print only refs that are merged")),
		OPT_NO_MERGED(&filter, N_("print only refs that are not merged")),
		OPT_CONTAINS(&filter.with_commit, N_("print only refs which contain the commit")),
		OPT_NO_CONTAINS(&filter.no_commit, N_("print only refs which don't contain the commit")),
		OPT_BOOL(0, "ignore-case", &icase, N_("sorting and filtering are case insensitive")),
		OPT_END(),
	};

	memset(&array, 0, sizeof(array));
	memset(&filter, 0, sizeof(filter));

	format.format = "%(objectname) %(objecttype)\t%(refname)";

	git_config(git_default_config, NULL);

	parse_options(argc, argv, prefix, opts, for_each_ref_usage, 0);
	if (maxcount < 0) {
		error("invalid --count argument: `%d'", maxcount);
		usage_with_options(for_each_ref_usage, opts);
	}
	if (HAS_MULTI_BITS(format.quote_style)) {
		error("more than one quoting style?");
		usage_with_options(for_each_ref_usage, opts);
	}
	if (verify_ref_format(&format))
		usage_with_options(for_each_ref_usage, opts);

	if (!sorting)
		sorting = ref_default_sorting();
	sorting->ignore_case = icase;
	filter.ignore_case = icase;

	filter.name_patterns = argv;
	filter.match_as_path = 1;
	filter_refs(&array, &filter, FILTER_REFS_ALL | FILTER_REFS_INCLUDE_BROKEN);
	ref_array_sort(sorting, &array);

	if (!maxcount || array.nr < maxcount)
		maxcount = array.nr;
	for (i = 0; i < maxcount; i++)
		show_ref_array_item(array.items[i], &format);
	ref_array_clear(&array);
	return 0;
}