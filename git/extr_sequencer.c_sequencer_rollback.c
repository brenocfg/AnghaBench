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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct replay_opts {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int error_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_head_file () ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 scalar_t__ parse_oid_hex (int /*<<< orphan*/ ,struct object_id*,char const**) ; 
 scalar_t__ reset_merge (struct object_id*) ; 
 int /*<<< orphan*/  rollback_is_safe () ; 
 int rollback_single_pick (struct repository*) ; 
 int sequencer_remove_state (struct replay_opts*) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*) ; 

int sequencer_rollback(struct repository *r, struct replay_opts *opts)
{
	FILE *f;
	struct object_id oid;
	struct strbuf buf = STRBUF_INIT;
	const char *p;

	f = fopen(git_path_head_file(), "r");
	if (!f && errno == ENOENT) {
		/*
		 * There is no multiple-cherry-pick in progress.
		 * If CHERRY_PICK_HEAD or REVERT_HEAD indicates
		 * a single-cherry-pick in progress, abort that.
		 */
		return rollback_single_pick(r);
	}
	if (!f)
		return error_errno(_("cannot open '%s'"), git_path_head_file());
	if (strbuf_getline_lf(&buf, f)) {
		error(_("cannot read '%s': %s"), git_path_head_file(),
		      ferror(f) ?  strerror(errno) : _("unexpected end of file"));
		fclose(f);
		goto fail;
	}
	fclose(f);
	if (parse_oid_hex(buf.buf, &oid, &p) || *p != '\0') {
		error(_("stored pre-cherry-pick HEAD file '%s' is corrupt"),
			git_path_head_file());
		goto fail;
	}
	if (is_null_oid(&oid)) {
		error(_("cannot abort from a branch yet to be born"));
		goto fail;
	}

	if (!rollback_is_safe()) {
		/* Do not error, just do not rollback */
		warning(_("You seem to have moved HEAD. "
			  "Not rewinding, check your HEAD!"));
	} else
	if (reset_merge(&oid))
		goto fail;
	strbuf_release(&buf);
	return sequencer_remove_state(opts);
fail:
	strbuf_release(&buf);
	return -1;
}