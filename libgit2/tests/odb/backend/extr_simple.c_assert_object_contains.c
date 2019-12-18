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
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 scalar_t__ git_odb_object_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_object_contains(git_odb_object *obj, const char *expected)
{
	const char *actual = (const char *) git_odb_object_data(obj);

	cl_assert_equal_s(actual, expected);
}