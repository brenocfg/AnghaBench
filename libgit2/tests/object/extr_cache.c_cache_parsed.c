#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/ * sha; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_data ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *cache_parsed(void *arg)
{
	int i;
	git_oid oid;
	git_object *obj;

	for (i = ((int *)arg)[1]; g_data[i].sha != NULL; i += 2) {
		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));
		cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));
		cl_assert(g_data[i].type == git_object_type(obj));
		git_object_free(obj);
	}

	for (i = 0; i < ((int *)arg)[1]; i += 2) {
		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));
		cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));
		cl_assert(g_data[i].type == git_object_type(obj));
		git_object_free(obj);
	}

	return arg;
}