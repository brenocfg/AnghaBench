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
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__exact_rename(void)
{
	const char *content =
	    "---\n"
	    " old_name.c => new_name.c | 0\n"
	    " 1 file changed, 0 insertions(+), 0 deletions(-)\n"
	    " rename old_name.c => new_name.c  (100%)\n"
	    "\n"
	    "diff --git a/old_name.c b/new_name.c\n"
	    "similarity index 100%\n"
	    "rename from old_name.c\n"
	    "rename to new_name.c\n"
	    "-- \n"
	    "2.9.3\n";
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(
		&diff, content, strlen(content)));
	git_diff_free(diff);
}