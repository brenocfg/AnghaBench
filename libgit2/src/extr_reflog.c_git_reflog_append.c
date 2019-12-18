#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_10__ {char* msg; int /*<<< orphan*/  const oid_cur; int /*<<< orphan*/  const oid_old; int /*<<< orphan*/  committer; } ;
typedef  TYPE_1__ git_reflog_entry ;
struct TYPE_11__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_reflog ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_OID_HEX_ZERO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* git__calloc (int,int) ; 
 char* git__strndup (char const*,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry__free (TYPE_1__*) ; 
 TYPE_1__* git_reflog_entry_byindex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_signature_dup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t strlen (char const*) ; 

int git_reflog_append(git_reflog *reflog, const git_oid *new_oid, const git_signature *committer, const char *msg)
{
	const git_reflog_entry *previous;
	git_reflog_entry *entry;

	assert(reflog && new_oid && committer);

	entry = git__calloc(1, sizeof(git_reflog_entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	if ((git_signature_dup(&entry->committer, committer)) < 0)
		goto cleanup;

	if (msg != NULL) {
		size_t i, msglen = strlen(msg);

		if ((entry->msg = git__strndup(msg, msglen)) == NULL)
			goto cleanup;

		/*
		 * Replace all newlines with spaces, except for
		 * the final trailing newline.
		 */
		for (i = 0; i < msglen; i++)
			if (entry->msg[i] == '\n')
				entry->msg[i] = ' ';
	}

	previous = git_reflog_entry_byindex(reflog, 0);

	if (previous == NULL)
		git_oid_fromstr(&entry->oid_old, GIT_OID_HEX_ZERO);
	else
		git_oid_cpy(&entry->oid_old, &previous->oid_cur);

	git_oid_cpy(&entry->oid_cur, new_oid);

	if (git_vector_insert(&reflog->entries, entry) < 0)
		goto cleanup;

	return 0;

cleanup:
	git_reflog_entry__free(entry);
	return -1;
}