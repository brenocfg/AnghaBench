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
struct rev_info {int /*<<< orphan*/ * commits; } ;
struct repository {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_REV_FLAGS ; 
 int /*<<< orphan*/  bisect_common (struct rev_info*) ; 
 int /*<<< orphan*/  bisect_rev_setup (struct repository*,struct rev_info*,char const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_commit_marks_many (int,struct commit**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_ancestors(struct repository *r, int rev_nr,
			   struct commit **rev, const char *prefix)
{
	struct rev_info revs;
	int res;

	bisect_rev_setup(r, &revs, prefix, "^%s", "%s", 0);

	bisect_common(&revs);
	res = (revs.commits != NULL);

	/* Clean up objects used, as they will be reused. */
	clear_commit_marks_many(rev_nr, rev, ALL_REV_FLAGS);

	return res;
}