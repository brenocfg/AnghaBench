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
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_IDENT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  add_blob_and_filter (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_filter_lookup (int /*<<< orphan*/ ) ; 

void test_filter_ident__to_odb(void)
{
	git_filter_list *fl;
	git_filter *ident;

	cl_git_pass(git_filter_list_new(
		&fl, g_repo, GIT_FILTER_TO_ODB, 0));

	ident = git_filter_lookup(GIT_FILTER_IDENT);
	cl_assert(ident != NULL);

	cl_git_pass(git_filter_list_push(fl, ident, NULL));

	add_blob_and_filter(
		"Hello\n$Id$\nFun stuff\n",
		fl, "Hello\n$Id$\nFun stuff\n");
	add_blob_and_filter(
		"Hello\n$Id: b69e2387aafcaf73c4de5b9ab59abe27fdadee30$\nFun stuff\n",
		fl, "Hello\n$Id$\nFun stuff\n");
	add_blob_and_filter(
		"Hello\n$Id: Any junk you may have left here$\nFun stuff\n",
		fl, "Hello\n$Id$\nFun stuff\n");
	add_blob_and_filter(
		"Hello\n$Id:$\nFun stuff\n",
		fl, "Hello\n$Id$\nFun stuff\n");
	add_blob_and_filter(
		"Hello\n$Id:x$\nFun stuff\n",
		fl, "Hello\n$Id$\nFun stuff\n");

	add_blob_and_filter(
		"$Id$\nAt the start\n", fl, "$Id$\nAt the start\n");
	add_blob_and_filter(
		"$Id: lots of random text that should be removed from here$\nAt the start\n", fl, "$Id$\nAt the start\n");
	add_blob_and_filter(
		"$Id: lots of random text that should not be removed without a terminator\nAt the start\n", fl, "$Id: lots of random text that should not be removed without a terminator\nAt the start\n");

	add_blob_and_filter(
		"At the end\n$Id$", fl, "At the end\n$Id$");
	add_blob_and_filter(
		"At the end\n$Id:$", fl, "At the end\n$Id$");
	add_blob_and_filter(
		"At the end\n$Id:asdfasdf$", fl, "At the end\n$Id$");
	add_blob_and_filter(
		"At the end\n$Id", fl, "At the end\n$Id");
	add_blob_and_filter(
		"At the end\n$IddI", fl, "At the end\n$IddI");

	add_blob_and_filter("$Id$", fl, "$Id$");
	add_blob_and_filter("$Id: any$", fl, "$Id$");
	add_blob_and_filter("$Id: any long stuff goes here you see$", fl, "$Id$");
	add_blob_and_filter("$Id: ", fl, "$Id: ");
	add_blob_and_filter("$Id", fl, "$Id");
	add_blob_and_filter("$I", fl, "$I");
	add_blob_and_filter("Id$", fl, "Id$");

	git_filter_list_free(fl);
}