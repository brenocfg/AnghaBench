#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ inmemory; } ;
typedef  TYPE_1__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_REBASE_TYPE_MERGE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int rebase_commit_inmemory (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*) ; 
 int rebase_commit_merge (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*) ; 

int git_rebase_commit(
	git_oid *id,
	git_rebase *rebase,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message)
{
	int error;

	assert(rebase && committer);

	if (rebase->inmemory)
		error = rebase_commit_inmemory(
			id, rebase, author, committer, message_encoding, message);
	else if (rebase->type == GIT_REBASE_TYPE_MERGE)
		error = rebase_commit_merge(
			id, rebase, author, committer, message_encoding, message);
	else
		abort();

	return error;
}