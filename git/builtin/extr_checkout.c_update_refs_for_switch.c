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
struct strbuf {char* buf; } ;
struct checkout_opts {char* new_branch; char* new_orphan_branch; scalar_t__ force_detach; int /*<<< orphan*/  quiet; scalar_t__ branch_exists; scalar_t__ new_branch_force; int /*<<< orphan*/  track; int /*<<< orphan*/  new_branch_log; } ;
struct branch_info {char* name; char* path; TYPE_2__* commit; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 char* _ (char*) ; 
 scalar_t__ advice_detached_head ; 
 int /*<<< orphan*/  create_branch (int /*<<< orphan*/ ,char*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ create_symref (char*,char*,char*) ; 
 int /*<<< orphan*/  delete_reflog (char*) ; 
 int /*<<< orphan*/  describe_detached_head (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  detach_advice (char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* mkpathdup (char*,char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_exists (char*) ; 
 scalar_t__ reflog_exists (char*) ; 
 int /*<<< orphan*/  remove_branch_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report_tracking (struct branch_info*) ; 
 int safe_create_reflog (char*,int,struct strbuf*) ; 
 int /*<<< orphan*/  setup_branch_path (struct branch_info*) ; 
 int /*<<< orphan*/  should_autocreate_reflog (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  update_ref (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_refs_for_switch(const struct checkout_opts *opts,
				   struct branch_info *old_branch_info,
				   struct branch_info *new_branch_info)
{
	struct strbuf msg = STRBUF_INIT;
	const char *old_desc, *reflog_msg;
	if (opts->new_branch) {
		if (opts->new_orphan_branch) {
			char *refname;

			refname = mkpathdup("refs/heads/%s", opts->new_orphan_branch);
			if (opts->new_branch_log &&
			    !should_autocreate_reflog(refname)) {
				int ret;
				struct strbuf err = STRBUF_INIT;

				ret = safe_create_reflog(refname, 1, &err);
				if (ret) {
					fprintf(stderr, _("Can not do reflog for '%s': %s\n"),
						opts->new_orphan_branch, err.buf);
					strbuf_release(&err);
					free(refname);
					return;
				}
				strbuf_release(&err);
			}
			free(refname);
		}
		else
			create_branch(the_repository,
				      opts->new_branch, new_branch_info->name,
				      opts->new_branch_force ? 1 : 0,
				      opts->new_branch_force ? 1 : 0,
				      opts->new_branch_log,
				      opts->quiet,
				      opts->track);
		new_branch_info->name = opts->new_branch;
		setup_branch_path(new_branch_info);
	}

	old_desc = old_branch_info->name;
	if (!old_desc && old_branch_info->commit)
		old_desc = oid_to_hex(&old_branch_info->commit->object.oid);

	reflog_msg = getenv("GIT_REFLOG_ACTION");
	if (!reflog_msg)
		strbuf_addf(&msg, "checkout: moving from %s to %s",
			old_desc ? old_desc : "(invalid)", new_branch_info->name);
	else
		strbuf_insert(&msg, 0, reflog_msg, strlen(reflog_msg));

	if (!strcmp(new_branch_info->name, "HEAD") && !new_branch_info->path && !opts->force_detach) {
		/* Nothing to do. */
	} else if (opts->force_detach || !new_branch_info->path) {	/* No longer on any branch. */
		update_ref(msg.buf, "HEAD", &new_branch_info->commit->object.oid, NULL,
			   REF_NO_DEREF, UPDATE_REFS_DIE_ON_ERR);
		if (!opts->quiet) {
			if (old_branch_info->path &&
			    advice_detached_head && !opts->force_detach)
				detach_advice(new_branch_info->name);
			describe_detached_head(_("HEAD is now at"), new_branch_info->commit);
		}
	} else if (new_branch_info->path) {	/* Switch branches. */
		if (create_symref("HEAD", new_branch_info->path, msg.buf) < 0)
			die(_("unable to update HEAD"));
		if (!opts->quiet) {
			if (old_branch_info->path && !strcmp(new_branch_info->path, old_branch_info->path)) {
				if (opts->new_branch_force)
					fprintf(stderr, _("Reset branch '%s'\n"),
						new_branch_info->name);
				else
					fprintf(stderr, _("Already on '%s'\n"),
						new_branch_info->name);
			} else if (opts->new_branch) {
				if (opts->branch_exists)
					fprintf(stderr, _("Switched to and reset branch '%s'\n"), new_branch_info->name);
				else
					fprintf(stderr, _("Switched to a new branch '%s'\n"), new_branch_info->name);
			} else {
				fprintf(stderr, _("Switched to branch '%s'\n"),
					new_branch_info->name);
			}
		}
		if (old_branch_info->path && old_branch_info->name) {
			if (!ref_exists(old_branch_info->path) && reflog_exists(old_branch_info->path))
				delete_reflog(old_branch_info->path);
		}
	}
	remove_branch_state(the_repository, !opts->quiet);
	strbuf_release(&msg);
	if (!opts->quiet &&
	    (new_branch_info->path || (!opts->force_detach && !strcmp(new_branch_info->name, "HEAD"))))
		report_tracking(new_branch_info);
}