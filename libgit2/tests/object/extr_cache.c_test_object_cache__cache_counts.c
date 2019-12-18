#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ size; int /*<<< orphan*/ * sha; } ;
struct TYPE_6__ {int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OPT_SET_CACHE_OBJECT_LIMIT ; 
 scalar_t__ cache_limit ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_5__* g_data ; 
 TYPE_1__* g_repo ; 
 scalar_t__ git_cache_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_open (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ object_type ; 

void test_object_cache__cache_counts(void)
{
	int i, start, nonmatching = 0;
	git_oid oid;
	git_odb_object *odb_obj;
	git_object *obj;
	git_odb *odb;

	git_libgit2_opts(GIT_OPT_SET_CACHE_OBJECT_LIMIT, object_type, cache_limit);

	cl_git_pass(git_repository_open(&g_repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_repository_odb(&odb, g_repo));

	start = (int)git_cache_size(&g_repo->objects);

	for (i = 0; g_data[i].sha != NULL; ++i) {
		int count = (int)git_cache_size(&g_repo->objects);

		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));

		/* alternate between loading raw and parsed objects */
		if ((i & 1) == 0) {
			cl_git_pass(git_odb_read(&odb_obj, odb, &oid));
			cl_assert(g_data[i].type == git_odb_object_type(odb_obj));
			git_odb_object_free(odb_obj);
		} else {
			cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));
			cl_assert(g_data[i].type == git_object_type(obj));
			git_object_free(obj);
		}

		if ((g_data[i].type == object_type && g_data[i].size >= cache_limit) ||
		    (g_data[i].type != object_type && g_data[i].type == GIT_OBJECT_BLOB))
			cl_assert_equal_i(count, (int)git_cache_size(&g_repo->objects));
		else {
			cl_assert_equal_i(count + 1, (int)git_cache_size(&g_repo->objects));
			nonmatching++;
		}
	}

	cl_assert_equal_i(nonmatching, (int)git_cache_size(&g_repo->objects) - start);

	for (i = 0; g_data[i].sha != NULL; ++i) {
		int count = (int)git_cache_size(&g_repo->objects);

		cl_git_pass(git_oid_fromstr(&oid, g_data[i].sha));
		cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));
		cl_assert(g_data[i].type == git_object_type(obj));
		git_object_free(obj);

		cl_assert_equal_i(count, (int)git_cache_size(&g_repo->objects));
	}

	git_odb_free(odb);
}