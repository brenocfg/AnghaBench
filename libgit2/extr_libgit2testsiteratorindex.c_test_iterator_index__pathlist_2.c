#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
struct TYPE_10__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_12__ {char* start; char* end; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 TYPE_2__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_index__pathlist_2(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;
	git_vector filelist = GIT_VECTOR_INIT;
	int default_icase, expect;

	g_repo = cl_git_sandbox_init("icase");

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_pass(git_vector_init(&filelist, 100, &git__strcmp_cb));
	cl_git_pass(git_vector_insert(&filelist, "0"));
	cl_git_pass(git_vector_insert(&filelist, "c"));
	cl_git_pass(git_vector_insert(&filelist, "D"));
	cl_git_pass(git_vector_insert(&filelist, "e"));
	cl_git_pass(git_vector_insert(&filelist, "k/"));
	cl_git_pass(git_vector_insert(&filelist, "k.a"));
	cl_git_pass(git_vector_insert(&filelist, "k.b"));
	cl_git_pass(git_vector_insert(&filelist, "kZZZZZZZ"));

	/* In this test we DO NOT force a case setting on the index. */
	default_icase = ((git_index_caps(index) & GIT_INDEX_CAPABILITY_IGNORE_CASE) != 0);

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;

	i_opts.start = "b";
	i_opts.end = "k/D";

	/* (c D e k/1 k/a k/B k/c k/D) vs (c e k/1 k/B k/D) */
	expect = default_icase ? 8 : 5;

	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, expect, NULL, expect, NULL);
	git_iterator_free(i);

	git_index_free(index);
	git_vector_free(&filelist);
}