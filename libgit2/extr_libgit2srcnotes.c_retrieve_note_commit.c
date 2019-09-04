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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 scalar_t__ git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int normalize_namespace (char**,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int retrieve_note_commit(
	git_commit **commit_out,
	char **notes_ref_out,
	git_repository *repo,
	const char *notes_ref)
{
	int error;
	git_oid oid;

	if ((error = normalize_namespace(notes_ref_out, repo, notes_ref)) < 0)
		return error;

	if ((error = git_reference_name_to_id(&oid, repo, *notes_ref_out)) < 0)
		return error;

	if (git_commit_lookup(commit_out, repo, &oid) < 0)
		return error;

	return 0;
}