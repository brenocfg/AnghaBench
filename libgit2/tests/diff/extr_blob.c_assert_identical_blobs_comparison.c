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
struct TYPE_3__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_identical_blobs_comparison(diff_expects *expected)
{
	cl_assert_equal_i(1, expected->files);
	cl_assert_equal_i(1, expected->file_status[GIT_DELTA_UNMODIFIED]);
	cl_assert_equal_i(0, expected->hunks);
	cl_assert_equal_i(0, expected->lines);
}