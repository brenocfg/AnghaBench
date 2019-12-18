#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_revwalk__push_options ;
struct TYPE_4__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int git_revwalk__push_commit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_revwalk__push_ref(git_revwalk *walk, const char *refname, const git_revwalk__push_options *opts)
{
	git_oid oid;

	if (git_reference_name_to_id(&oid, walk->repo, refname) < 0)
		return -1;

	return git_revwalk__push_commit(walk, &oid, opts);
}