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
struct group_test_data {int dummy; } ;
struct group {int /*<<< orphan*/  gr_name; } ;

/* Variables and functions */
 scalar_t__ compare_group (struct group*,struct group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_group (struct group*) ; 
 struct group* getgrnam (int /*<<< orphan*/ ) ; 
 scalar_t__ group_check_ambiguity (struct group_test_data*,struct group*) ; 
 scalar_t__ group_test_correctness (struct group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
group_test_getgrnam(struct group *grp_model, void *mdata)
{
	struct group *grp;

	printf("testing getgrnam() with the following data:\n");
	dump_group(grp_model);

	grp = getgrnam(grp_model->gr_name);
	if (group_test_correctness(grp, NULL) != 0)
		goto errfin;

	if (compare_group(grp, grp_model, NULL) != 0 &&
	    group_check_ambiguity((struct group_test_data *)mdata, grp) != 0)
	    goto errfin;

	return (0);

errfin:
	return (-1);
}