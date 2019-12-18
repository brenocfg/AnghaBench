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
struct ref_lock {char* ref_name; int /*<<< orphan*/  old_oid; } ;
struct object_id {int dummy; } ;
struct files_ref_store {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  clear_loose_ref_cache (struct files_ref_store*) ; 
 scalar_t__ commit_ref (struct ref_lock*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files_assert_main_repository (struct files_ref_store*,char*) ; 
 scalar_t__ files_log_ref_write (struct files_ref_store*,char*,int /*<<< orphan*/ *,struct object_id const*,char const*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* refs_resolve_ref_unsafe (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 

__attribute__((used)) static int commit_ref_update(struct files_ref_store *refs,
			     struct ref_lock *lock,
			     const struct object_id *oid, const char *logmsg,
			     struct strbuf *err)
{
	files_assert_main_repository(refs, "commit_ref_update");

	clear_loose_ref_cache(refs);
	if (files_log_ref_write(refs, lock->ref_name,
				&lock->old_oid, oid,
				logmsg, 0, err)) {
		char *old_msg = strbuf_detach(err, NULL);
		strbuf_addf(err, "cannot update the ref '%s': %s",
			    lock->ref_name, old_msg);
		free(old_msg);
		unlock_ref(lock);
		return -1;
	}

	if (strcmp(lock->ref_name, "HEAD") != 0) {
		/*
		 * Special hack: If a branch is updated directly and HEAD
		 * points to it (may happen on the remote side of a push
		 * for example) then logically the HEAD reflog should be
		 * updated too.
		 * A generic solution implies reverse symref information,
		 * but finding all symrefs pointing to the given branch
		 * would be rather costly for this rare event (the direct
		 * update of a branch) to be worth it.  So let's cheat and
		 * check with HEAD only which should cover 99% of all usage
		 * scenarios (even 100% of the default ones).
		 */
		int head_flag;
		const char *head_ref;

		head_ref = refs_resolve_ref_unsafe(&refs->base, "HEAD",
						   RESOLVE_REF_READING,
						   NULL, &head_flag);
		if (head_ref && (head_flag & REF_ISSYMREF) &&
		    !strcmp(head_ref, lock->ref_name)) {
			struct strbuf log_err = STRBUF_INIT;
			if (files_log_ref_write(refs, "HEAD",
						&lock->old_oid, oid,
						logmsg, 0, &log_err)) {
				error("%s", log_err.buf);
				strbuf_release(&log_err);
			}
		}
	}

	if (commit_ref(lock)) {
		strbuf_addf(err, "couldn't set '%s'", lock->ref_name);
		unlock_ref(lock);
		return -1;
	}

	unlock_ref(lock);
	return 0;
}