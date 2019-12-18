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
struct strbuf {char const* buf; } ;
struct repository {int dummy; } ;
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  enum branch_track { ____Placeholder_branch_track } branch_track ;

/* Variables and functions */
 int BRANCH_TRACK_EXPLICIT ; 
 int BRANCH_TRACK_OVERRIDE ; 
 int /*<<< orphan*/  LOG_REFS_NORMAL ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 scalar_t__ advice_set_upstream_failure ; 
 int /*<<< orphan*/  advise (char*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int dwim_ref (char const*,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid_mb (char const*,struct object_id*) ; 
 int /*<<< orphan*/  log_all_ref_updates ; 
 struct commit* lookup_commit_reference (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,char const*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct strbuf*) ; 
 int /*<<< orphan*/  setup_tracking (char const*,char*,int,int) ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* upstream_advice ; 
 char* upstream_missing ; 
 char* upstream_not_branch ; 
 scalar_t__ validate_branchname (char const*,struct strbuf*) ; 
 scalar_t__ validate_new_branchname (char const*,struct strbuf*,int) ; 
 int /*<<< orphan*/  validate_remote_tracking_branch (char*) ; 
 char* xstrfmt (char*,char const*) ; 

void create_branch(struct repository *r,
		   const char *name, const char *start_name,
		   int force, int clobber_head_ok, int reflog,
		   int quiet, enum branch_track track)
{
	struct commit *commit;
	struct object_id oid;
	char *real_ref;
	struct strbuf ref = STRBUF_INIT;
	int forcing = 0;
	int dont_change_ref = 0;
	int explicit_tracking = 0;

	if (track == BRANCH_TRACK_EXPLICIT || track == BRANCH_TRACK_OVERRIDE)
		explicit_tracking = 1;

	if ((track == BRANCH_TRACK_OVERRIDE || clobber_head_ok)
	    ? validate_branchname(name, &ref)
	    : validate_new_branchname(name, &ref, force)) {
		if (!force)
			dont_change_ref = 1;
		else
			forcing = 1;
	}

	real_ref = NULL;
	if (get_oid_mb(start_name, &oid)) {
		if (explicit_tracking) {
			if (advice_set_upstream_failure) {
				error(_(upstream_missing), start_name);
				advise(_(upstream_advice));
				exit(1);
			}
			die(_(upstream_missing), start_name);
		}
		die(_("Not a valid object name: '%s'."), start_name);
	}

	switch (dwim_ref(start_name, strlen(start_name), &oid, &real_ref)) {
	case 0:
		/* Not branching from any existing branch */
		if (explicit_tracking)
			die(_(upstream_not_branch), start_name);
		break;
	case 1:
		/* Unique completion -- good, only if it is a real branch */
		if (!starts_with(real_ref, "refs/heads/") &&
		    validate_remote_tracking_branch(real_ref)) {
			if (explicit_tracking)
				die(_(upstream_not_branch), start_name);
			else
				real_ref = NULL;
		}
		break;
	default:
		die(_("Ambiguous object name: '%s'."), start_name);
		break;
	}

	if ((commit = lookup_commit_reference(r, &oid)) == NULL)
		die(_("Not a valid branch point: '%s'."), start_name);
	oidcpy(&oid, &commit->object.oid);

	if (reflog)
		log_all_ref_updates = LOG_REFS_NORMAL;

	if (!dont_change_ref) {
		struct ref_transaction *transaction;
		struct strbuf err = STRBUF_INIT;
		char *msg;

		if (forcing)
			msg = xstrfmt("branch: Reset to %s", start_name);
		else
			msg = xstrfmt("branch: Created from %s", start_name);

		transaction = ref_transaction_begin(&err);
		if (!transaction ||
		    ref_transaction_update(transaction, ref.buf,
					   &oid, forcing ? NULL : &null_oid,
					   0, msg, &err) ||
		    ref_transaction_commit(transaction, &err))
			die("%s", err.buf);
		ref_transaction_free(transaction);
		strbuf_release(&err);
		free(msg);
	}

	if (real_ref && track)
		setup_tracking(ref.buf + 11, real_ref, track, quiet);

	strbuf_release(&ref);
	free(real_ref);
}