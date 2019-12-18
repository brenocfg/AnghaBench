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
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int git_object_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_blob_dup(git_blob **out, git_blob *obj)
{
	return git_object_dup((git_object **)out, (git_object *)obj);
}