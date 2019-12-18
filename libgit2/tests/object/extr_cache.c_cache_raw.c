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
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/ * sha; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_data ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *cache_raw(void *arg)
{
	int i;
	git_oid oid;
	git_odb *odb;
	git_odb_object *odb_obj;

	cl_git_pass(git_repository_odb(&odb, g_repo));

	for (i = ((int *)arg)[1]; g_data[i].sha != NULL; i += 2) {
		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));
		cl_git_pass(git_odb_read(&odb_obj, odb, &oid));
		cl_assert(g_data[i].type == git_odb_object_type(odb_obj));
		git_odb_object_free(odb_obj);
	}

	for (i = 0; i < ((int *)arg)[1]; i += 2) {
		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));
		cl_git_pass(git_odb_read(&odb_obj, odb, &oid));
		cl_assert(g_data[i].type == git_odb_object_type(odb_obj));
		git_odb_object_free(odb_obj);
	}

	git_odb_free(odb);

	return arg;
}