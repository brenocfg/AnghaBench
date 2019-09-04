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
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  commit; } ;
typedef  TYPE_1__ git_blame__origin ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool same_suspect(git_blame__origin *a, git_blame__origin *b)
{
	if (a == b)
		return true;
	if (git_oid_cmp(git_commit_id(a->commit), git_commit_id(b->commit)))
		return false;
	return 0 == strcmp(a->path, b->path);
}