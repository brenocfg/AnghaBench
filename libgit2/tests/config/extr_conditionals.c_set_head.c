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

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_create_head (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_head(git_repository *repo, const char *name)
{
	cl_git_pass(git_repository_create_head(git_repository_path(repo), name));
}