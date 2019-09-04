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
 int /*<<< orphan*/  GIT_EUSER ; 
 int /*<<< orphan*/  do_push (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void test_online_push__b5_cancel(void)
{
	const char *specs[] = { "refs/heads/b5:refs/heads/b5" };
	do_push(specs, ARRAY_SIZE(specs), NULL, 0, NULL, 0, GIT_EUSER, 1, 1);
}