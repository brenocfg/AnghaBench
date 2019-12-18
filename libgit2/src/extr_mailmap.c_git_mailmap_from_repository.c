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
typedef  int /*<<< orphan*/  git_mailmap ;

/* Variables and functions */
 int git_mailmap_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mailmap_add_from_repository (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_mailmap_from_repository(git_mailmap **out, git_repository *repo)
{
	int error = git_mailmap_new(out);
	if (error < 0)
		return error;
	mailmap_add_from_repository(*out, repo);
	return 0;
}