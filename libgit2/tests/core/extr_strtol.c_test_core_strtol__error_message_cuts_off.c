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
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_l32_fails (char*,int) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void test_core_strtol__error_message_cuts_off(void)
{
	assert_l32_fails("2147483657foobar", 10);
	cl_assert(strstr(git_error_last()->message, "2147483657") != NULL);
	cl_assert(strstr(git_error_last()->message, "foobar") == NULL);
}