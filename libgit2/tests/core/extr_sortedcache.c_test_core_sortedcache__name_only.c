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
typedef  int /*<<< orphan*/  git_sortedcache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,void*) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * git_sortedcache_entry (int /*<<< orphan*/ *,int) ; 
 size_t git_sortedcache_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_sortedcache_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sortedcache_lookup_index (size_t*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sortedcache_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_upsert (void**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sortedcache_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_only_cmp ; 

void test_core_sortedcache__name_only(void)
{
	git_sortedcache *sc;
	void *item;
	size_t pos;

	cl_git_pass(git_sortedcache_new(
		&sc, 0, NULL, NULL, name_only_cmp, NULL));

	cl_git_pass(git_sortedcache_wlock(sc));
	cl_git_pass(git_sortedcache_upsert(&item, sc, "aaa"));
	cl_git_pass(git_sortedcache_upsert(&item, sc, "bbb"));
	cl_git_pass(git_sortedcache_upsert(&item, sc, "zzz"));
	cl_git_pass(git_sortedcache_upsert(&item, sc, "mmm"));
	cl_git_pass(git_sortedcache_upsert(&item, sc, "iii"));
	git_sortedcache_wunlock(sc);

	cl_assert_equal_sz(5, git_sortedcache_entrycount(sc));

	cl_assert((item = git_sortedcache_lookup(sc, "aaa")) != NULL);
	cl_assert_equal_s("aaa", item);
	cl_assert((item = git_sortedcache_lookup(sc, "mmm")) != NULL);
	cl_assert_equal_s("mmm", item);
	cl_assert((item = git_sortedcache_lookup(sc, "zzz")) != NULL);
	cl_assert_equal_s("zzz", item);
	cl_assert(git_sortedcache_lookup(sc, "qqq") == NULL);

	cl_assert((item = git_sortedcache_entry(sc, 0)) != NULL);
	cl_assert_equal_s("aaa", item);
	cl_assert((item = git_sortedcache_entry(sc, 1)) != NULL);
	cl_assert_equal_s("bbb", item);
	cl_assert((item = git_sortedcache_entry(sc, 2)) != NULL);
	cl_assert_equal_s("iii", item);
	cl_assert((item = git_sortedcache_entry(sc, 3)) != NULL);
	cl_assert_equal_s("mmm", item);
	cl_assert((item = git_sortedcache_entry(sc, 4)) != NULL);
	cl_assert_equal_s("zzz", item);
	cl_assert(git_sortedcache_entry(sc, 5) == NULL);

	cl_git_pass(git_sortedcache_lookup_index(&pos, sc, "aaa"));
	cl_assert_equal_sz(0, pos);
	cl_git_pass(git_sortedcache_lookup_index(&pos, sc, "iii"));
	cl_assert_equal_sz(2, pos);
	cl_git_pass(git_sortedcache_lookup_index(&pos, sc, "zzz"));
	cl_assert_equal_sz(4, pos);
	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sortedcache_lookup_index(&pos, sc, "abc"));

	git_sortedcache_clear(sc, true);

	cl_assert_equal_sz(0, git_sortedcache_entrycount(sc));
	cl_assert(git_sortedcache_entry(sc, 0) == NULL);
	cl_assert(git_sortedcache_lookup(sc, "aaa") == NULL);
	cl_assert(git_sortedcache_entry(sc, 0) == NULL);

	git_sortedcache_free(sc);
}