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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct patch_util {struct object_id oid; int /*<<< orphan*/  i; int /*<<< orphan*/  patch; } ;
struct diff_options {int /*<<< orphan*/  file; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  DIFF_COMMIT ; 
 int /*<<< orphan*/  DIFF_FILE_NEW ; 
 int /*<<< orphan*/  DIFF_FILE_OLD ; 
 int /*<<< orphan*/  DIFF_RESET ; 
 char* diff_get_color_opt (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_unique_abbrev (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  pp_commit_easy (int /*<<< orphan*/ ,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void output_pair_header(struct diff_options *diffopt,
			       int patch_no_width,
			       struct strbuf *buf,
			       struct strbuf *dashes,
			       struct patch_util *a_util,
			       struct patch_util *b_util)
{
	struct object_id *oid = a_util ? &a_util->oid : &b_util->oid;
	struct commit *commit;
	char status;
	const char *color_reset = diff_get_color_opt(diffopt, DIFF_RESET);
	const char *color_old = diff_get_color_opt(diffopt, DIFF_FILE_OLD);
	const char *color_new = diff_get_color_opt(diffopt, DIFF_FILE_NEW);
	const char *color_commit = diff_get_color_opt(diffopt, DIFF_COMMIT);
	const char *color;

	if (!dashes->len)
		strbuf_addchars(dashes, '-',
				strlen(find_unique_abbrev(oid,
							  DEFAULT_ABBREV)));

	if (!b_util) {
		color = color_old;
		status = '<';
	} else if (!a_util) {
		color = color_new;
		status = '>';
	} else if (strcmp(a_util->patch, b_util->patch)) {
		color = color_commit;
		status = '!';
	} else {
		color = color_commit;
		status = '=';
	}

	strbuf_reset(buf);
	strbuf_addstr(buf, status == '!' ? color_old : color);
	if (!a_util)
		strbuf_addf(buf, "%*s:  %s ", patch_no_width, "-", dashes->buf);
	else
		strbuf_addf(buf, "%*d:  %s ", patch_no_width, a_util->i + 1,
			    find_unique_abbrev(&a_util->oid, DEFAULT_ABBREV));

	if (status == '!')
		strbuf_addf(buf, "%s%s", color_reset, color);
	strbuf_addch(buf, status);
	if (status == '!')
		strbuf_addf(buf, "%s%s", color_reset, color_new);

	if (!b_util)
		strbuf_addf(buf, " %*s:  %s", patch_no_width, "-", dashes->buf);
	else
		strbuf_addf(buf, " %*d:  %s", patch_no_width, b_util->i + 1,
			    find_unique_abbrev(&b_util->oid, DEFAULT_ABBREV));

	commit = lookup_commit_reference(the_repository, oid);
	if (commit) {
		if (status == '!')
			strbuf_addf(buf, "%s%s", color_reset, color);

		strbuf_addch(buf, ' ');
		pp_commit_easy(CMIT_FMT_ONELINE, commit, buf);
	}
	strbuf_addf(buf, "%s\n", color_reset);

	fwrite(buf->buf, buf->len, 1, diffopt->file);
}