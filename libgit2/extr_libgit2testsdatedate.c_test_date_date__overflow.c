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
typedef  scalar_t__ git_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__date_parse (scalar_t__*,char*) ; 

void test_date_date__overflow(void)
{
#ifdef __LP64__
   git_time_t d2038, d2039;

   /* This is expected to fail on a 32-bit machine. */
   cl_git_pass(git__date_parse(&d2038, "2038-1-1"));
   cl_git_pass(git__date_parse(&d2039, "2039-1-1"));
   cl_assert(d2038 < d2039);
#endif
}