#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct checkdiff_t {char const* filename; int ws_rule; int ctxlen; int status; scalar_t__ flags; int /*<<< orphan*/  conflict_marker_size; struct diff_options* o; scalar_t__ lineno; } ;
typedef  struct checkdiff_t xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  struct checkdiff_t xdemitconf_t ;
struct emit_callback {int ws_rule; int blank_at_eof_in_postimage; } ;
struct TYPE_4__ {int check_failed; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  file; TYPE_2__* repo; } ;
struct diff_filespec {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int WS_BLANK_AT_EOF ; 
 int /*<<< orphan*/  check_blank_at_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct emit_callback*) ; 
 int /*<<< orphan*/  checkdiff_consume ; 
 int /*<<< orphan*/  checkdiff_consume_hunk ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ diff_filespec_is_binary (TYPE_2__*,struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_free_filespec_data (struct diff_filespec*) ; 
 scalar_t__ fill_mmfile (TYPE_2__*,int /*<<< orphan*/ *,struct diff_filespec*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  ll_merge_marker_size (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memset (struct checkdiff_t*,int /*<<< orphan*/ ,int) ; 
 char* whitespace_error_string (int) ; 
 int whitespace_rule (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ xdi_diff_outf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct checkdiff_t*,struct checkdiff_t*,struct checkdiff_t*) ; 

__attribute__((used)) static void builtin_checkdiff(const char *name_a, const char *name_b,
			      const char *attr_path,
			      struct diff_filespec *one,
			      struct diff_filespec *two,
			      struct diff_options *o)
{
	mmfile_t mf1, mf2;
	struct checkdiff_t data;

	if (!two)
		return;

	memset(&data, 0, sizeof(data));
	data.filename = name_b ? name_b : name_a;
	data.lineno = 0;
	data.o = o;
	data.ws_rule = whitespace_rule(o->repo->index, attr_path);
	data.conflict_marker_size = ll_merge_marker_size(o->repo->index, attr_path);

	if (fill_mmfile(o->repo, &mf1, one) < 0 ||
	    fill_mmfile(o->repo, &mf2, two) < 0)
		die("unable to read files to diff");

	/*
	 * All the other codepaths check both sides, but not checking
	 * the "old" side here is deliberate.  We are checking the newly
	 * introduced changes, and as long as the "new" side is text, we
	 * can and should check what it introduces.
	 */
	if (diff_filespec_is_binary(o->repo, two))
		goto free_and_return;
	else {
		/* Crazy xdl interfaces.. */
		xpparam_t xpp;
		xdemitconf_t xecfg;

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		xecfg.ctxlen = 1; /* at least one context line */
		xpp.flags = 0;
		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume_hunk,
				  checkdiff_consume, &data,
				  &xpp, &xecfg))
			die("unable to generate checkdiff for %s", one->path);

		if (data.ws_rule & WS_BLANK_AT_EOF) {
			struct emit_callback ecbdata;
			int blank_at_eof;

			ecbdata.ws_rule = data.ws_rule;
			check_blank_at_eof(&mf1, &mf2, &ecbdata);
			blank_at_eof = ecbdata.blank_at_eof_in_postimage;

			if (blank_at_eof) {
				static char *err;
				if (!err)
					err = whitespace_error_string(WS_BLANK_AT_EOF);
				fprintf(o->file, "%s:%d: %s.\n",
					data.filename, blank_at_eof, err);
				data.status = 1; /* report errors */
			}
		}
	}
 free_and_return:
	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
	if (data.status)
		o->flags.check_failed = 1;
}