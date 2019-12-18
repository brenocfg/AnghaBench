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
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int dummy; } ;
struct patch_util {int shown; scalar_t__ matching; } ;
struct diff_options {int output_format; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; struct patch_util* util; } ;

/* Variables and functions */
 int DIFF_FORMAT_NO_OUTPUT ; 
 struct strbuf STRBUF_INIT ; 
 int decimal_width (int) ; 
 int /*<<< orphan*/  output_pair_header (struct diff_options*,int,struct strbuf*,struct strbuf*,struct patch_util*,struct patch_util*) ; 
 int /*<<< orphan*/  patch_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct diff_options*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void output(struct string_list *a, struct string_list *b,
		   struct diff_options *diffopt)
{
	struct strbuf buf = STRBUF_INIT, dashes = STRBUF_INIT;
	int patch_no_width = decimal_width(1 + (a->nr > b->nr ? a->nr : b->nr));
	int i = 0, j = 0;

	/*
	 * We assume the user is really more interested in the second argument
	 * ("newer" version). To that end, we print the output in the order of
	 * the RHS (the `b` parameter). To put the LHS (the `a` parameter)
	 * commits that are no longer in the RHS into a good place, we place
	 * them once we have shown all of their predecessors in the LHS.
	 */

	while (i < a->nr || j < b->nr) {
		struct patch_util *a_util, *b_util;
		a_util = i < a->nr ? a->items[i].util : NULL;
		b_util = j < b->nr ? b->items[j].util : NULL;

		/* Skip all the already-shown commits from the LHS. */
		while (i < a->nr && a_util->shown)
			a_util = ++i < a->nr ? a->items[i].util : NULL;

		/* Show unmatched LHS commit whose predecessors were shown. */
		if (i < a->nr && a_util->matching < 0) {
			output_pair_header(diffopt, patch_no_width,
					   &buf, &dashes, a_util, NULL);
			i++;
			continue;
		}

		/* Show unmatched RHS commits. */
		while (j < b->nr && b_util->matching < 0) {
			output_pair_header(diffopt, patch_no_width,
					   &buf, &dashes, NULL, b_util);
			b_util = ++j < b->nr ? b->items[j].util : NULL;
		}

		/* Show matching LHS/RHS pair. */
		if (j < b->nr) {
			a_util = a->items[b_util->matching].util;
			output_pair_header(diffopt, patch_no_width,
					   &buf, &dashes, a_util, b_util);
			if (!(diffopt->output_format & DIFF_FORMAT_NO_OUTPUT))
				patch_diff(a->items[b_util->matching].string,
					   b->items[j].string, diffopt);
			a_util->shown = 1;
			j++;
		}
	}
	strbuf_release(&buf);
	strbuf_release(&dashes);
}