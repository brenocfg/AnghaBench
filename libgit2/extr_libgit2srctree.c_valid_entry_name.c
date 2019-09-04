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
 int GIT_PATH_REJECT_DOT_GIT ; 
 int GIT_PATH_REJECT_SLASH ; 
 int GIT_PATH_REJECT_TRAVERSAL ; 
 scalar_t__ git_path_isvalid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int valid_entry_name(git_repository *repo, const char *filename)
{
	return *filename != '\0' &&
		git_path_isvalid(repo, filename, 0,
		GIT_PATH_REJECT_TRAVERSAL | GIT_PATH_REJECT_DOT_GIT | GIT_PATH_REJECT_SLASH);
}