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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_2__ {size_t total; scalar_t__ repo; int /*<<< orphan*/ ** parents; } ;
typedef  TYPE_1__ commit_parent_data ;

/* Variables and functions */
 int /*<<< orphan*/  const* git_commit_id (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_commit_owner (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const git_oid *commit_parent_from_array(size_t curr, void *payload)
{
	commit_parent_data *data = payload;
	const git_commit *commit;
	if (curr >= data->total)
		return NULL;
	commit = data->parents[curr];
	if (git_commit_owner(commit) != data->repo)
		return NULL;
	return git_commit_id(commit);
}