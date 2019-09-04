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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  do_push (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_online_push__expressions(void)
{
	/* TODO: Expressions in refspecs doesn't actually work yet */
	const char *specs_left_expr[] = { "refs/heads/b2~1:refs/heads/b2" };

	/* TODO: Find a more precise way of checking errors than a exit code of -1. */
	do_push(specs_left_expr, ARRAY_SIZE(specs_left_expr),
		NULL, 0,
		NULL, 0, -1, 0, 0);
}