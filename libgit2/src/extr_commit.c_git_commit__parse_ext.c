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
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int commit_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_size (int /*<<< orphan*/ *) ; 

int git_commit__parse_ext(git_commit *commit, git_odb_object *odb_obj, unsigned int flags)
{
	return commit_parse(commit, git_odb_object_data(odb_obj), git_odb_object_size(odb_obj), flags);
}