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
typedef  int /*<<< orphan*/  git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_tag_list_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

int git_tag_list(git_strarray *tag_names, git_repository *repo)
{
	return git_tag_list_match(tag_names, "", repo);
}