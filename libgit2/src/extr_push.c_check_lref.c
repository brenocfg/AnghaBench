#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_push ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_lref(git_push *push, char *ref)
{
	/* lref must be resolvable to an existing object */
	git_object *obj;
	int error = git_revparse_single(&obj, push->repo, ref);
	git_object_free(obj);

	if (!error)
		return 0;

	if (error == GIT_ENOTFOUND)
		git_error_set(GIT_ERROR_REFERENCE,
			"src refspec '%s' does not match any existing object", ref);
	else
		git_error_set(GIT_ERROR_INVALID, "not a valid reference '%s'", ref);
	return -1;
}