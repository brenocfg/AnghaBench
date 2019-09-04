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
struct diffstat_t {int dummy; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct TYPE_2__ {int has_changes; scalar_t__ diff_from_contents; scalar_t__ exit_with_status; scalar_t__ dirstat_by_line; } ;
struct diff_options {int output_format; int close_file; TYPE_1__ flags; scalar_t__ found_changes; int /*<<< orphan*/  file; int /*<<< orphan*/  format_callback_data; int /*<<< orphan*/  (* format_callback ) (struct diff_queue_struct*,struct diff_options*,int /*<<< orphan*/ ) ;scalar_t__ stat_sep; scalar_t__ color_moved; } ;
struct diff_filepair {int dummy; } ;

/* Variables and functions */
 int DIFF_FORMAT_CALLBACK ; 
 int DIFF_FORMAT_CHECKDIFF ; 
 int DIFF_FORMAT_DIFFSTAT ; 
 int DIFF_FORMAT_DIRSTAT ; 
 int DIFF_FORMAT_NAME ; 
 int DIFF_FORMAT_NAME_STATUS ; 
 int DIFF_FORMAT_NO_OUTPUT ; 
 int DIFF_FORMAT_NUMSTAT ; 
 int DIFF_FORMAT_PATCH ; 
 int DIFF_FORMAT_RAW ; 
 int DIFF_FORMAT_SHORTSTAT ; 
 int DIFF_FORMAT_SUMMARY ; 
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (struct diff_queue_struct*) ; 
 int /*<<< orphan*/  DIFF_SYMBOL_SEPARATOR ; 
 int /*<<< orphan*/  DIFF_SYMBOL_STAT_SEP ; 
 scalar_t__ check_pair_status (struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_flush_patch (struct diff_filepair*,struct diff_options*) ; 
 int /*<<< orphan*/  diff_flush_patch_all_file_pairs (struct diff_options*) ; 
 int /*<<< orphan*/  diff_flush_stat (struct diff_filepair*,struct diff_options*,struct diffstat_t*) ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  diff_summary (struct diff_options*,struct diff_filepair*) ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_one_pair (struct diff_filepair*,struct diff_options*) ; 
 int /*<<< orphan*/  free (struct diff_filepair**) ; 
 int /*<<< orphan*/  free_diffstat_info (struct diffstat_t*) ; 
 int /*<<< orphan*/  is_summary_empty (struct diff_queue_struct*) ; 
 int /*<<< orphan*/  memset (struct diffstat_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  show_dirstat (struct diff_options*) ; 
 int /*<<< orphan*/  show_dirstat_by_line (struct diffstat_t*,struct diff_options*) ; 
 int /*<<< orphan*/  show_numstat (struct diffstat_t*,struct diff_options*) ; 
 int /*<<< orphan*/  show_shortstats (struct diffstat_t*,struct diff_options*) ; 
 int /*<<< orphan*/  show_stats (struct diffstat_t*,struct diff_options*) ; 
 int /*<<< orphan*/  stub1 (struct diff_queue_struct*,struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfopen (char*,char*) ; 

void diff_flush(struct diff_options *options)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	int i, output_format = options->output_format;
	int separator = 0;
	int dirstat_by_line = 0;

	/*
	 * Order: raw, stat, summary, patch
	 * or:    name/name-status/checkdiff (other bits clear)
	 */
	if (!q->nr)
		goto free_queue;

	if (output_format & (DIFF_FORMAT_RAW |
			     DIFF_FORMAT_NAME |
			     DIFF_FORMAT_NAME_STATUS |
			     DIFF_FORMAT_CHECKDIFF)) {
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (check_pair_status(p))
				flush_one_pair(p, options);
		}
		separator++;
	}

	if (output_format & DIFF_FORMAT_DIRSTAT && options->flags.dirstat_by_line)
		dirstat_by_line = 1;

	if (output_format & (DIFF_FORMAT_DIFFSTAT|DIFF_FORMAT_SHORTSTAT|DIFF_FORMAT_NUMSTAT) ||
	    dirstat_by_line) {
		struct diffstat_t diffstat;

		memset(&diffstat, 0, sizeof(struct diffstat_t));
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (check_pair_status(p))
				diff_flush_stat(p, options, &diffstat);
		}
		if (output_format & DIFF_FORMAT_NUMSTAT)
			show_numstat(&diffstat, options);
		if (output_format & DIFF_FORMAT_DIFFSTAT)
			show_stats(&diffstat, options);
		if (output_format & DIFF_FORMAT_SHORTSTAT)
			show_shortstats(&diffstat, options);
		if (output_format & DIFF_FORMAT_DIRSTAT && dirstat_by_line)
			show_dirstat_by_line(&diffstat, options);
		free_diffstat_info(&diffstat);
		separator++;
	}
	if ((output_format & DIFF_FORMAT_DIRSTAT) && !dirstat_by_line)
		show_dirstat(options);

	if (output_format & DIFF_FORMAT_SUMMARY && !is_summary_empty(q)) {
		for (i = 0; i < q->nr; i++) {
			diff_summary(options, q->queue[i]);
		}
		separator++;
	}

	if (output_format & DIFF_FORMAT_NO_OUTPUT &&
	    options->flags.exit_with_status &&
	    options->flags.diff_from_contents) {
		/*
		 * run diff_flush_patch for the exit status. setting
		 * options->file to /dev/null should be safe, because we
		 * aren't supposed to produce any output anyway.
		 */
		if (options->close_file)
			fclose(options->file);
		options->file = xfopen("/dev/null", "w");
		options->close_file = 1;
		options->color_moved = 0;
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (check_pair_status(p))
				diff_flush_patch(p, options);
			if (options->found_changes)
				break;
		}
	}

	if (output_format & DIFF_FORMAT_PATCH) {
		if (separator) {
			emit_diff_symbol(options, DIFF_SYMBOL_SEPARATOR, NULL, 0, 0);
			if (options->stat_sep)
				/* attach patch instead of inline */
				emit_diff_symbol(options, DIFF_SYMBOL_STAT_SEP,
						 NULL, 0, 0);
		}

		diff_flush_patch_all_file_pairs(options);
	}

	if (output_format & DIFF_FORMAT_CALLBACK)
		options->format_callback(q, options, options->format_callback_data);

	for (i = 0; i < q->nr; i++)
		diff_free_filepair(q->queue[i]);
free_queue:
	free(q->queue);
	DIFF_QUEUE_CLEAR(q);
	if (options->close_file)
		fclose(options->file);

	/*
	 * Report the content-level differences with HAS_CHANGES;
	 * diff_addremove/diff_change does not set the bit when
	 * DIFF_FROM_CONTENTS is in effect (e.g. with -w).
	 */
	if (options->flags.diff_from_contents) {
		if (options->found_changes)
			options->flags.has_changes = 1;
		else
			options->flags.has_changes = 0;
	}
}