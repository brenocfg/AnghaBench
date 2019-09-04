#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t expect_idx; int /*<<< orphan*/ ** expect; int /*<<< orphan*/  cancel_after; } ;
typedef  TYPE_1__ check_walkup_info ;

/* Variables and functions */
 int CANCEL_VALUE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int check_one_walkup_step(void *ref, const char *path)
{
	check_walkup_info *info = (check_walkup_info *)ref;

	if (!info->cancel_after) {
		cl_assert_equal_s(info->expect[info->expect_idx], "[CANCEL]");
		return CANCEL_VALUE;
	}
	info->cancel_after--;

	cl_assert(info->expect[info->expect_idx] != NULL);
	cl_assert_equal_s(info->expect[info->expect_idx], path);
	info->expect_idx++;

	return 0;
}