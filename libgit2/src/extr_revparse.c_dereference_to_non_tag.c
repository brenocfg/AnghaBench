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
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_TAG ; 
 int git_object_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int git_tag_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dereference_to_non_tag(git_object **out, git_object *obj)
{
	if (git_object_type(obj) == GIT_OBJECT_TAG)
		return git_tag_peel(out, (git_tag *)obj);

	return git_object_dup(out, obj);
}