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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; int /*<<< orphan*/  use_color; int /*<<< orphan*/  output_format; } ;
struct rev_info {int diff; int disable_stdin; int no_commit_id; TYPE_2__ diffopt; scalar_t__ abbrev; } ;
struct repository {int dummy; } ;
struct replay_opts {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  log_tree_opt ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  GIT_COLOR_NEVER ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char*) ; 
 int error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_commit_subject (char const*,char const**) ; 
 int /*<<< orphan*/  fopen (int /*<<< orphan*/ ,char*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dir (struct replay_opts*) ; 
 int log_tree_commit (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  memset (struct rev_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rebase_path_stopped_sha () ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 char* short_commit_name (struct commit*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 
 scalar_t__ update_ref (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_message (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int make_patch(struct repository *r,
		      struct commit *commit,
		      struct replay_opts *opts)
{
	struct strbuf buf = STRBUF_INIT;
	struct rev_info log_tree_opt;
	const char *subject, *p;
	int res = 0;

	p = short_commit_name(commit);
	if (write_message(p, strlen(p), rebase_path_stopped_sha(), 1) < 0)
		return -1;
	if (update_ref("rebase", "REBASE_HEAD", &commit->object.oid,
		       NULL, REF_NO_DEREF, UPDATE_REFS_MSG_ON_ERR))
		res |= error(_("could not update %s"), "REBASE_HEAD");

	strbuf_addf(&buf, "%s/patch", get_dir(opts));
	memset(&log_tree_opt, 0, sizeof(log_tree_opt));
	repo_init_revisions(r, &log_tree_opt, NULL);
	log_tree_opt.abbrev = 0;
	log_tree_opt.diff = 1;
	log_tree_opt.diffopt.output_format = DIFF_FORMAT_PATCH;
	log_tree_opt.disable_stdin = 1;
	log_tree_opt.no_commit_id = 1;
	log_tree_opt.diffopt.file = fopen(buf.buf, "w");
	log_tree_opt.diffopt.use_color = GIT_COLOR_NEVER;
	if (!log_tree_opt.diffopt.file)
		res |= error_errno(_("could not open '%s'"), buf.buf);
	else {
		res |= log_tree_commit(&log_tree_opt, commit);
		fclose(log_tree_opt.diffopt.file);
	}
	strbuf_reset(&buf);

	strbuf_addf(&buf, "%s/message", get_dir(opts));
	if (!file_exists(buf.buf)) {
		const char *commit_buffer = get_commit_buffer(commit, NULL);
		find_commit_subject(commit_buffer, &subject);
		res |= write_message(subject, strlen(subject), buf.buf, 1);
		unuse_commit_buffer(commit, commit_buffer);
	}
	strbuf_release(&buf);

	return res;
}