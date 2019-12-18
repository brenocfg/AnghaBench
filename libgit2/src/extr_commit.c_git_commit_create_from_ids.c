#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {size_t member_0; int /*<<< orphan*/  const** member_1; } ;
typedef  TYPE_1__ commit_parent_oids ;

/* Variables and functions */
 int /*<<< orphan*/  commit_parent_from_ids ; 
 int git_commit__create_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

int git_commit_create_from_ids(
	git_oid *id,
	git_repository *repo,
	const char *update_ref,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_oid *tree,
	size_t parent_count,
	const git_oid *parents[])
{
	commit_parent_oids data = { parent_count, parents };

	return git_commit__create_internal(
		id, repo, update_ref, author, committer,
		message_encoding, message, tree,
		commit_parent_from_ids, &data, true);
}