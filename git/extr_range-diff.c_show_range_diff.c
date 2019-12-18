#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct strbuf {int dummy; } ;
struct TYPE_2__ {int suppress_diff_headers; int dual_color_diffed_diffs; int suppress_hunk_header_line_count; } ;
struct diff_options {struct strbuf* output_prefix_data; int /*<<< orphan*/  output_prefix; TYPE_1__ flags; scalar_t__ output_format; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 scalar_t__ DIFF_FORMAT_PATCH ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  diff_setup (struct diff_options*) ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  find_exact_matches (struct string_list*,struct string_list*) ; 
 int /*<<< orphan*/  get_correspondences (struct string_list*,struct string_list*,int) ; 
 int /*<<< orphan*/  memcpy (struct diff_options*,struct diff_options*,int) ; 
 int /*<<< orphan*/  output (struct string_list*,struct string_list*,struct diff_options*) ; 
 int /*<<< orphan*/  output_prefix_cb ; 
 scalar_t__ read_patches (char const*,struct string_list*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 

int show_range_diff(const char *range1, const char *range2,
		    int creation_factor, int dual_color,
		    struct diff_options *diffopt)
{
	int res = 0;

	struct string_list branch1 = STRING_LIST_INIT_DUP;
	struct string_list branch2 = STRING_LIST_INIT_DUP;

	if (read_patches(range1, &branch1))
		res = error(_("could not parse log for '%s'"), range1);
	if (!res && read_patches(range2, &branch2))
		res = error(_("could not parse log for '%s'"), range2);

	if (!res) {
		struct diff_options opts;
		struct strbuf indent = STRBUF_INIT;

		if (diffopt)
			memcpy(&opts, diffopt, sizeof(opts));
		else
			diff_setup(&opts);

		if (!opts.output_format)
			opts.output_format = DIFF_FORMAT_PATCH;
		opts.flags.suppress_diff_headers = 1;
		opts.flags.dual_color_diffed_diffs = dual_color;
		opts.flags.suppress_hunk_header_line_count = 1;
		opts.output_prefix = output_prefix_cb;
		strbuf_addstr(&indent, "    ");
		opts.output_prefix_data = &indent;
		diff_setup_done(&opts);

		find_exact_matches(&branch1, &branch2);
		get_correspondences(&branch1, &branch2, creation_factor);
		output(&branch1, &branch2, &opts);

		strbuf_release(&indent);
	}

	string_list_clear(&branch1, 1);
	string_list_clear(&branch2, 1);

	return res;
}