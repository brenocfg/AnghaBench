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
typedef  int /*<<< orphan*/  git_refspec ;

/* Variables and functions */
 unsigned int GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_ERROR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int git_refspec__parse (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void assert_refspec(unsigned int direction, const char *input, bool is_expected_to_be_valid)
{
	git_refspec refspec;
	int error;

	error = git_refspec__parse(&refspec, input, direction == GIT_DIRECTION_FETCH);
	git_refspec__dispose(&refspec);

	if (is_expected_to_be_valid)
		cl_assert_equal_i(0, error);
	else
		cl_assert_equal_i(GIT_ERROR, error);
}