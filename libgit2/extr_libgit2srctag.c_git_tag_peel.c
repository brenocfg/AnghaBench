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
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int git_tag_peel(git_object **tag_target, const git_tag *tag)
{
	return git_object_peel(tag_target, (const git_object *)tag, GIT_OBJECT_ANY);
}