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
struct TYPE_3__ {scalar_t__ name; int /*<<< orphan*/  oid; scalar_t__ symref_target; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_MASTER_FILE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ git__prefixcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int git_buf_puts (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int git_remote_ls (TYPE_1__ const***,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

int git_remote_default_branch(git_buf *out, git_remote *remote)
{
	const git_remote_head **heads;
	const git_remote_head *guess = NULL;
	const git_oid *head_id;
	size_t heads_len, i;
	int error;

	assert(out);

	if ((error = git_remote_ls(&heads, &heads_len, remote)) < 0)
		return error;

	if (heads_len == 0)
		return GIT_ENOTFOUND;

	if (strcmp(heads[0]->name, GIT_HEAD_FILE))
		return GIT_ENOTFOUND;

	git_buf_sanitize(out);
	/* the first one must be HEAD so if that has the symref info, we're done */
	if (heads[0]->symref_target)
		return git_buf_puts(out, heads[0]->symref_target);

	/*
	 * If there's no symref information, we have to look over them
	 * and guess. We return the first match unless the master
	 * branch is a candidate. Then we return the master branch.
	 */
	head_id = &heads[0]->oid;

	for (i = 1; i < heads_len; i++) {
		if (git_oid_cmp(head_id, &heads[i]->oid))
			continue;

		if (git__prefixcmp(heads[i]->name, GIT_REFS_HEADS_DIR))
			continue;

		if (!guess) {
			guess = heads[i];
			continue;
		}

		if (!git__strcmp(GIT_REFS_HEADS_MASTER_FILE, heads[i]->name)) {
			guess = heads[i];
			break;
		}
	}

	if (!guess)
		return GIT_ENOTFOUND;

	return git_buf_puts(out, guess->name);
}