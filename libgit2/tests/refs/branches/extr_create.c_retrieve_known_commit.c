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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  retrieve_target_from_oid (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void retrieve_known_commit(git_commit **commit, git_repository *repo)
{
	retrieve_target_from_oid(commit, repo, "e90810b8df3");
}