#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct diff_options {int line_termination; int output_format; int /*<<< orphan*/  file; int /*<<< orphan*/  prefix_length; int /*<<< orphan*/  abbrev; } ;
struct diff_filepair {int status; TYPE_2__* two; TYPE_1__* one; scalar_t__ score; } ;
struct TYPE_4__ {int mode; char* path; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int mode; char* path; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int DIFF_FORMAT_NAME_STATUS ; 
 scalar_t__ DIFF_STATUS_COPIED ; 
 scalar_t__ DIFF_STATUS_RENAMED ; 
 char* diff_aligned_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* diff_line_prefix (struct diff_options*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int similarity_index (struct diff_filepair*) ; 
 int /*<<< orphan*/  strip_prefix (int /*<<< orphan*/ ,char const**,char const**) ; 
 int /*<<< orphan*/  write_name_quoted (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void diff_flush_raw(struct diff_filepair *p, struct diff_options *opt)
{
	int line_termination = opt->line_termination;
	int inter_name_termination = line_termination ? '\t' : '\0';

	fprintf(opt->file, "%s", diff_line_prefix(opt));
	if (!(opt->output_format & DIFF_FORMAT_NAME_STATUS)) {
		fprintf(opt->file, ":%06o %06o %s ", p->one->mode, p->two->mode,
			diff_aligned_abbrev(&p->one->oid, opt->abbrev));
		fprintf(opt->file, "%s ",
			diff_aligned_abbrev(&p->two->oid, opt->abbrev));
	}
	if (p->score) {
		fprintf(opt->file, "%c%03d%c", p->status, similarity_index(p),
			inter_name_termination);
	} else {
		fprintf(opt->file, "%c%c", p->status, inter_name_termination);
	}

	if (p->status == DIFF_STATUS_COPIED ||
	    p->status == DIFF_STATUS_RENAMED) {
		const char *name_a, *name_b;
		name_a = p->one->path;
		name_b = p->two->path;
		strip_prefix(opt->prefix_length, &name_a, &name_b);
		write_name_quoted(name_a, opt->file, inter_name_termination);
		write_name_quoted(name_b, opt->file, line_termination);
	} else {
		const char *name_a, *name_b;
		name_a = p->one->mode ? p->one->path : p->two->path;
		name_b = NULL;
		strip_prefix(opt->prefix_length, &name_a, &name_b);
		write_name_quoted(name_a, opt->file, line_termination);
	}
}