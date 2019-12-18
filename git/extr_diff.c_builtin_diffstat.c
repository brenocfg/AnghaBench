#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  interhunkctxlen; int /*<<< orphan*/  ctxlen; int /*<<< orphan*/  anchors_nr; int /*<<< orphan*/  anchors; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  TYPE_2__ xdemitconf_t ;
struct diffstat_t {int dummy; } ;
struct diffstat_file {int is_interesting; int is_unmerged; int is_binary; void* added; void* deleted; int /*<<< orphan*/  is_renamed; int /*<<< orphan*/  comments; } ;
struct TYPE_7__ {scalar_t__ stat_with_summary; } ;
struct diff_options {int /*<<< orphan*/  interhunkcontext; int /*<<< orphan*/  context; int /*<<< orphan*/  anchors_nr; int /*<<< orphan*/  anchors; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  repo; TYPE_1__ flags; } ;
struct diff_filespec {int /*<<< orphan*/  path; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  oid; } ;
struct diff_filepair {scalar_t__ status; scalar_t__ score; } ;
typedef  int /*<<< orphan*/  mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_PAIR_UNMERGED (struct diff_filepair*) ; 
 scalar_t__ DIFF_STATUS_MODIFIED ; 
 scalar_t__ DIFF_STATUS_UNKNOWN ; 
 void* count_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ diff_filespec_is_binary (int /*<<< orphan*/ ,struct diff_filespec*) ; 
 void* diff_filespec_size (int /*<<< orphan*/ ,struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_free_filespec_data (struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_populate_filespec (int /*<<< orphan*/ ,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 struct diffstat_file* diffstat_add (struct diffstat_t*,char const*,char const*) ; 
 int /*<<< orphan*/  diffstat_consume ; 
 int /*<<< orphan*/  discard_hunk_line ; 
 scalar_t__ fill_mmfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct diff_filespec*) ; 
 int /*<<< orphan*/  get_compact_summary (struct diff_filepair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdi_diff_outf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct diffstat_t*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void builtin_diffstat(const char *name_a, const char *name_b,
			     struct diff_filespec *one,
			     struct diff_filespec *two,
			     struct diffstat_t *diffstat,
			     struct diff_options *o,
			     struct diff_filepair *p)
{
	mmfile_t mf1, mf2;
	struct diffstat_file *data;
	int same_contents;
	int complete_rewrite = 0;

	if (!DIFF_PAIR_UNMERGED(p)) {
		if (p->status == DIFF_STATUS_MODIFIED && p->score)
			complete_rewrite = 1;
	}

	data = diffstat_add(diffstat, name_a, name_b);
	data->is_interesting = p->status != DIFF_STATUS_UNKNOWN;
	if (o->flags.stat_with_summary)
		data->comments = get_compact_summary(p, data->is_renamed);

	if (!one || !two) {
		data->is_unmerged = 1;
		return;
	}

	same_contents = oideq(&one->oid, &two->oid);

	if (diff_filespec_is_binary(o->repo, one) ||
	    diff_filespec_is_binary(o->repo, two)) {
		data->is_binary = 1;
		if (same_contents) {
			data->added = 0;
			data->deleted = 0;
		} else {
			data->added = diff_filespec_size(o->repo, two);
			data->deleted = diff_filespec_size(o->repo, one);
		}
	}

	else if (complete_rewrite) {
		diff_populate_filespec(o->repo, one, 0);
		diff_populate_filespec(o->repo, two, 0);
		data->deleted = count_lines(one->data, one->size);
		data->added = count_lines(two->data, two->size);
	}

	else if (!same_contents) {
		/* Crazy xdl interfaces.. */
		xpparam_t xpp;
		xdemitconf_t xecfg;

		if (fill_mmfile(o->repo, &mf1, one) < 0 ||
		    fill_mmfile(o->repo, &mf2, two) < 0)
			die("unable to read files to diff");

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		xpp.flags = o->xdl_opts;
		xpp.anchors = o->anchors;
		xpp.anchors_nr = o->anchors_nr;
		xecfg.ctxlen = o->context;
		xecfg.interhunkctxlen = o->interhunkcontext;
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  diffstat_consume, diffstat, &xpp, &xecfg))
			die("unable to generate diffstat for %s", one->path);
	}

	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
}