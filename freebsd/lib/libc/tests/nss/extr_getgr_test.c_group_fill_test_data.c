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
struct group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct group_test_data*,struct group*) ; 
 int /*<<< orphan*/  endgrent () ; 
 struct group* getgrent () ; 
 int /*<<< orphan*/  group ; 
 scalar_t__ group_test_correctness (struct group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgroupent (int) ; 

__attribute__((used)) static int
group_fill_test_data(struct group_test_data *td)
{
	struct group *grp;

	setgroupent(1);
	while ((grp = getgrent()) != NULL) {
		if (group_test_correctness(grp, NULL) == 0)
			TEST_DATA_APPEND(group, td, grp);
		else
			return (-1);
	}
	endgrent();

	return (0);
}