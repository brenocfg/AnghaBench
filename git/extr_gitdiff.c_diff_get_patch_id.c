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
struct patch_id_t {int ctxlen; scalar_t__ flags; int /*<<< orphan*/ * ctx; } ;
typedef  struct patch_id_t xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  struct patch_id_t xdemitconf_t ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_options {TYPE_1__* repo; } ;
struct diff_filepair {scalar_t__ status; TYPE_2__* one; TYPE_2__* two; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  git_SHA_CTX ;
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  path; int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ DIFF_FILE_VALID (TYPE_2__*) ; 
 scalar_t__ DIFF_PAIR_UNMERGED (struct diff_filepair*) ; 
 scalar_t__ DIFF_STATUS_UNKNOWN ; 
 int GIT_SHA1_HEXSZ ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ diff_filespec_is_binary (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  diff_fill_oid_info (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct diff_queue_struct diff_queued_diff ; 
 scalar_t__ diff_unmodified_pair (struct diff_filepair*) ; 
 int /*<<< orphan*/  discard_hunk_line ; 
 int error (char*,...) ; 
 scalar_t__ fill_mmfile (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_SHA1_Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_SHA1_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct patch_id_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  patch_id_add_mode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  patch_id_add_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  patch_id_consume ; 
 int remove_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ xdi_diff_outf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct patch_id_t*,struct patch_id_t*,struct patch_id_t*) ; 

__attribute__((used)) static int diff_get_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	int i;
	git_SHA_CTX ctx;
	struct patch_id_t data;

	git_SHA1_Init(&ctx);
	memset(&data, 0, sizeof(struct patch_id_t));
	data.ctx = &ctx;

	for (i = 0; i < q->nr; i++) {
		xpparam_t xpp;
		xdemitconf_t xecfg;
		mmfile_t mf1, mf2;
		struct diff_filepair *p = q->queue[i];
		int len1, len2;

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		if (p->status == 0)
			return error("internal diff status error");
		if (p->status == DIFF_STATUS_UNKNOWN)
			continue;
		if (diff_unmodified_pair(p))
			continue;
		if ((DIFF_FILE_VALID(p->one) && S_ISDIR(p->one->mode)) ||
		    (DIFF_FILE_VALID(p->two) && S_ISDIR(p->two->mode)))
			continue;
		if (DIFF_PAIR_UNMERGED(p))
			continue;

		diff_fill_oid_info(p->one, options->repo->index);
		diff_fill_oid_info(p->two, options->repo->index);

		len1 = remove_space(p->one->path, strlen(p->one->path));
		len2 = remove_space(p->two->path, strlen(p->two->path));
		patch_id_add_string(&ctx, "diff--git");
		patch_id_add_string(&ctx, "a/");
		git_SHA1_Update(&ctx, p->one->path, len1);
		patch_id_add_string(&ctx, "b/");
		git_SHA1_Update(&ctx, p->two->path, len2);

		if (p->one->mode == 0) {
			patch_id_add_string(&ctx, "newfilemode");
			patch_id_add_mode(&ctx, p->two->mode);
			patch_id_add_string(&ctx, "---/dev/null");
			patch_id_add_string(&ctx, "+++b/");
			git_SHA1_Update(&ctx, p->two->path, len2);
		} else if (p->two->mode == 0) {
			patch_id_add_string(&ctx, "deletedfilemode");
			patch_id_add_mode(&ctx, p->one->mode);
			patch_id_add_string(&ctx, "---a/");
			git_SHA1_Update(&ctx, p->one->path, len1);
			patch_id_add_string(&ctx, "+++/dev/null");
		} else {
			patch_id_add_string(&ctx, "---a/");
			git_SHA1_Update(&ctx, p->one->path, len1);
			patch_id_add_string(&ctx, "+++b/");
			git_SHA1_Update(&ctx, p->two->path, len2);
		}

		if (diff_header_only)
			continue;

		if (fill_mmfile(options->repo, &mf1, p->one) < 0 ||
		    fill_mmfile(options->repo, &mf2, p->two) < 0)
			return error("unable to read files to diff");

		if (diff_filespec_is_binary(options->repo, p->one) ||
		    diff_filespec_is_binary(options->repo, p->two)) {
			git_SHA1_Update(&ctx, oid_to_hex(&p->one->oid),
					GIT_SHA1_HEXSZ);
			git_SHA1_Update(&ctx, oid_to_hex(&p->two->oid),
					GIT_SHA1_HEXSZ);
			continue;
		}

		xpp.flags = 0;
		xecfg.ctxlen = 3;
		xecfg.flags = 0;
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  patch_id_consume, &data, &xpp, &xecfg))
			return error("unable to generate patch-id diff for %s",
				     p->one->path);
	}

	git_SHA1_Final(oid->hash, &ctx);
	return 0;
}