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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_3__ {char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_odb_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_fromstrp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ one ; 
 int /*<<< orphan*/  write_object_files (TYPE_1__*) ; 

void test_odb_loose__exists(void)
{
	git_oid id, id2;
	git_odb *odb;

	write_object_files(&one);
	cl_git_pass(git_odb_open(&odb, "test-objects"));

	cl_git_pass(git_oid_fromstr(&id, one.id));
	cl_assert(git_odb_exists(odb, &id));

	cl_git_pass(git_oid_fromstrp(&id, "8b137891"));
	cl_git_pass(git_odb_exists_prefix(&id2, odb, &id, 8));
	cl_assert_equal_i(0, git_oid_streq(&id2, one.id));

	/* Test for a missing object */
	cl_git_pass(git_oid_fromstr(&id, "8b137891791fe96927ad78e64b0aad7bded08baa"));
	cl_assert(!git_odb_exists(odb, &id));

	cl_git_pass(git_oid_fromstrp(&id, "8b13789a"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_odb_exists_prefix(&id2, odb, &id, 8));

	git_odb_free(odb);
}