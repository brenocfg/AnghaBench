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
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__assert (int,char const*,int,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clar__assert_equal (char const*,int,char*,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_index_find (size_t*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void add_and_check_mode_(
	git_index *index, const char *filename, unsigned int expect_mode,
	const char *file, int line)
{
	size_t pos;
	const git_index_entry *entry;

	cl_git_pass(git_index_add_bypath(index, filename));

	clar__assert(!git_index_find(&pos, index, filename),
		file, line, "Cannot find index entry", NULL, 1);

	entry = git_index_get_byindex(index, pos);

	clar__assert_equal(file, line, "Expected mode does not match index",
		1, "%07o", (unsigned int)entry->mode, (unsigned int)expect_mode);
}