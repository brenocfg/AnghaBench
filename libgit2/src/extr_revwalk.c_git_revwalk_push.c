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
typedef  int /*<<< orphan*/  git_revwalk__push_options ;
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REVWALK__PUSH_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_revwalk__push_commit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int git_revwalk_push(git_revwalk *walk, const git_oid *oid)
{
	git_revwalk__push_options opts = GIT_REVWALK__PUSH_OPTIONS_INIT;

	assert(walk && oid);

	return git_revwalk__push_commit(walk, oid, &opts);
}