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
struct slot_results {char* http_code; int /*<<< orphan*/  curl_result; } ;
struct object_id {int dummy; } ;
struct ref {char* name; struct object_id old_oid; struct ref* next; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;
struct TYPE_2__ {char* url; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  DAV_DELETE ; 
 int MAXDEPTH ; 
 int /*<<< orphan*/  curl_setup_http_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dry_run ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  fetch_symref (char*,char**,struct object_id*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct active_request_slot* get_active_slot () ; 
 int /*<<< orphan*/  has_object_file (struct object_id*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 char* oid_to_hex (struct object_id*) ; 
 struct ref* remote_refs ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  verify_merge_base (struct object_id*,struct ref*) ; 
 char* xstrfmt (char*,char*,char*) ; 

__attribute__((used)) static int delete_remote_branch(const char *pattern, int force)
{
	struct ref *refs = remote_refs;
	struct ref *remote_ref = NULL;
	struct object_id head_oid;
	char *symref = NULL;
	int match;
	int patlen = strlen(pattern);
	int i;
	struct active_request_slot *slot;
	struct slot_results results;
	char *url;

	/* Find the remote branch(es) matching the specified branch name */
	for (match = 0; refs; refs = refs->next) {
		char *name = refs->name;
		int namelen = strlen(name);
		if (namelen < patlen ||
		    memcmp(name + namelen - patlen, pattern, patlen))
			continue;
		if (namelen != patlen && name[namelen - patlen - 1] != '/')
			continue;
		match++;
		remote_ref = refs;
	}
	if (match == 0)
		return error("No remote branch matches %s", pattern);
	if (match != 1)
		return error("More than one remote branch matches %s",
			     pattern);

	/*
	 * Remote HEAD must be a symref (not exactly foolproof; a remote
	 * symlink to a symref will look like a symref)
	 */
	fetch_symref("HEAD", &symref, &head_oid);
	if (!symref)
		return error("Remote HEAD is not a symref");

	/* Remote branch must not be the remote HEAD */
	for (i = 0; symref && i < MAXDEPTH; i++) {
		if (!strcmp(remote_ref->name, symref))
			return error("Remote branch %s is the current HEAD",
				     remote_ref->name);
		fetch_symref(symref, &symref, &head_oid);
	}

	/* Run extra sanity checks if delete is not forced */
	if (!force) {
		/* Remote HEAD must resolve to a known object */
		if (symref)
			return error("Remote HEAD symrefs too deep");
		if (is_null_oid(&head_oid))
			return error("Unable to resolve remote HEAD");
		if (!has_object_file(&head_oid))
			return error("Remote HEAD resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", oid_to_hex(&head_oid));

		/* Remote branch must resolve to a known object */
		if (is_null_oid(&remote_ref->old_oid))
			return error("Unable to resolve remote branch %s",
				     remote_ref->name);
		if (!has_object_file(&remote_ref->old_oid))
			return error("Remote branch %s resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", remote_ref->name, oid_to_hex(&remote_ref->old_oid));

		/* Remote branch must be an ancestor of remote HEAD */
		if (!verify_merge_base(&head_oid, remote_ref)) {
			return error("The branch '%s' is not an ancestor "
				     "of your current HEAD.\n"
				     "If you are sure you want to delete it,"
				     " run:\n\t'git http-push -D %s %s'",
				     remote_ref->name, repo->url, pattern);
		}
	}

	/* Send delete request */
	fprintf(stderr, "Removing remote branch '%s'\n", remote_ref->name);
	if (dry_run)
		return 0;
	url = xstrfmt("%s%s", repo->url, remote_ref->name);
	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http_get(slot->curl, url, DAV_DELETE);
	if (start_active_slot(slot)) {
		run_active_slot(slot);
		free(url);
		if (results.curl_result != CURLE_OK)
			return error("DELETE request failed (%d/%ld)",
				     results.curl_result, results.http_code);
	} else {
		free(url);
		return error("Unable to start DELETE request");
	}

	return 0;
}