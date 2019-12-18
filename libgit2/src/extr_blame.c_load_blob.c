#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  newest_commit; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; scalar_t__ final; scalar_t__ final_blob; TYPE_1__ options; int /*<<< orphan*/  repository; } ;
typedef  TYPE_2__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int git_commit_lookup (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_object_lookup_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_blob(git_blame *blame)
{
	int error;

	if (blame->final_blob) return 0;

	error = git_commit_lookup(&blame->final, blame->repository, &blame->options.newest_commit);
	if (error < 0)
		goto cleanup;
	error = git_object_lookup_bypath((git_object**)&blame->final_blob,
			(git_object*)blame->final, blame->path, GIT_OBJECT_BLOB);

cleanup:
	return error;
}