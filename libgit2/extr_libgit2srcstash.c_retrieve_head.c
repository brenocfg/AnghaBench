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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_EUNBORNBRANCH ; 
 int create_error (int,char*) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int retrieve_head(git_reference **out, git_repository *repo)
{
	int error = git_repository_head(out, repo);

	if (error == GIT_EUNBORNBRANCH)
		return create_error(error, "you do not have the initial commit yet.");

	return error;
}