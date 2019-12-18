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

/* Variables and functions */
 int /*<<< orphan*/  git_cached_obj_incref (int /*<<< orphan*/ *) ; 

int git_odb_object_dup(git_odb_object **dest, git_odb_object *source)
{
	git_cached_obj_incref(source);
	*dest = source;
	return 0;
}