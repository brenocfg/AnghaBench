#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct diff_options {int /*<<< orphan*/  file; int /*<<< orphan*/  repo; int /*<<< orphan*/  use_color; } ;
struct rev_info {struct diff_options diffopt; } ;
struct TYPE_11__ {unsigned int nr; TYPE_3__* ranges; } ;
struct TYPE_13__ {unsigned int nr; TYPE_5__* ranges; } ;
struct TYPE_9__ {TYPE_1__* ranges; } ;
struct diff_ranges {TYPE_6__ target; TYPE_2__ parent; } ;
struct line_log_data {TYPE_4__ ranges; struct diff_ranges diff; struct diff_filepair* pair; } ;
struct diff_filepair {TYPE_7__* two; TYPE_7__* one; } ;
struct TYPE_14__ {char* path; int /*<<< orphan*/  data; scalar_t__ oid_valid; } ;
struct TYPE_12__ {long end; long start; } ;
struct TYPE_10__ {long start; long end; } ;
struct TYPE_8__ {long start; long end; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_CONTEXT ; 
 int /*<<< orphan*/  DIFF_FILE_NEW ; 
 int /*<<< orphan*/  DIFF_FILE_OLD ; 
 int /*<<< orphan*/  DIFF_FRAGINFO ; 
 int /*<<< orphan*/  DIFF_METAINFO ; 
 int /*<<< orphan*/  DIFF_RESET ; 
 char* diff_get_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_line_ends (int /*<<< orphan*/ ,TYPE_7__*,long*,unsigned long**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 char* output_prefix (struct diff_options*) ; 
 int /*<<< orphan*/  print_line (char*,char,long,unsigned long*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_diff_hacky_one(struct rev_info *rev, struct line_log_data *range)
{
	unsigned int i, j = 0;
	long p_lines, t_lines;
	unsigned long *p_ends = NULL, *t_ends = NULL;
	struct diff_filepair *pair = range->pair;
	struct diff_ranges *diff = &range->diff;

	struct diff_options *opt = &rev->diffopt;
	char *prefix = output_prefix(opt);
	const char *c_reset = diff_get_color(opt->use_color, DIFF_RESET);
	const char *c_frag = diff_get_color(opt->use_color, DIFF_FRAGINFO);
	const char *c_meta = diff_get_color(opt->use_color, DIFF_METAINFO);
	const char *c_old = diff_get_color(opt->use_color, DIFF_FILE_OLD);
	const char *c_new = diff_get_color(opt->use_color, DIFF_FILE_NEW);
	const char *c_context = diff_get_color(opt->use_color, DIFF_CONTEXT);

	if (!pair || !diff)
		return;

	if (pair->one->oid_valid)
		fill_line_ends(rev->diffopt.repo, pair->one, &p_lines, &p_ends);
	fill_line_ends(rev->diffopt.repo, pair->two, &t_lines, &t_ends);

	fprintf(opt->file, "%s%sdiff --git a/%s b/%s%s\n", prefix, c_meta, pair->one->path, pair->two->path, c_reset);
	fprintf(opt->file, "%s%s--- %s%s%s\n", prefix, c_meta,
	       pair->one->oid_valid ? "a/" : "",
	       pair->one->oid_valid ? pair->one->path : "/dev/null",
	       c_reset);
	fprintf(opt->file, "%s%s+++ b/%s%s\n", prefix, c_meta, pair->two->path, c_reset);
	for (i = 0; i < range->ranges.nr; i++) {
		long p_start, p_end;
		long t_start = range->ranges.ranges[i].start;
		long t_end = range->ranges.ranges[i].end;
		long t_cur = t_start;
		unsigned int j_last;

		while (j < diff->target.nr && diff->target.ranges[j].end < t_start)
			j++;
		if (j == diff->target.nr || diff->target.ranges[j].start > t_end)
			continue;

		/* Scan ahead to determine the last diff that falls in this range */
		j_last = j;
		while (j_last < diff->target.nr && diff->target.ranges[j_last].start < t_end)
			j_last++;
		if (j_last > j)
			j_last--;

		/*
		 * Compute parent hunk headers: we know that the diff
		 * has the correct line numbers (but not all hunks).
		 * So it suffices to shift the start/end according to
		 * the line numbers of the first/last hunk(s) that
		 * fall in this range.
		 */
		if (t_start < diff->target.ranges[j].start)
			p_start = diff->parent.ranges[j].start - (diff->target.ranges[j].start-t_start);
		else
			p_start = diff->parent.ranges[j].start;
		if (t_end > diff->target.ranges[j_last].end)
			p_end = diff->parent.ranges[j_last].end + (t_end-diff->target.ranges[j_last].end);
		else
			p_end = diff->parent.ranges[j_last].end;

		if (!p_start && !p_end) {
			p_start = -1;
			p_end = -1;
		}

		/* Now output a diff hunk for this range */
		fprintf(opt->file, "%s%s@@ -%ld,%ld +%ld,%ld @@%s\n",
		       prefix, c_frag,
		       p_start+1, p_end-p_start, t_start+1, t_end-t_start,
		       c_reset);
		while (j < diff->target.nr && diff->target.ranges[j].start < t_end) {
			int k;
			for (; t_cur < diff->target.ranges[j].start; t_cur++)
				print_line(prefix, ' ', t_cur, t_ends, pair->two->data,
					   c_context, c_reset, opt->file);
			for (k = diff->parent.ranges[j].start; k < diff->parent.ranges[j].end; k++)
				print_line(prefix, '-', k, p_ends, pair->one->data,
					   c_old, c_reset, opt->file);
			for (; t_cur < diff->target.ranges[j].end && t_cur < t_end; t_cur++)
				print_line(prefix, '+', t_cur, t_ends, pair->two->data,
					   c_new, c_reset, opt->file);
			j++;
		}
		for (; t_cur < t_end; t_cur++)
			print_line(prefix, ' ', t_cur, t_ends, pair->two->data,
				   c_context, c_reset, opt->file);
	}

	free(p_ends);
	free(t_ends);
}