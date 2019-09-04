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
 int /*<<< orphan*/  GIT_UNUSED (unsigned int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 

__attribute__((used)) static int cb_status__expected_path(const char *p, unsigned int s, void *payload)
{
	const char *expected_path = (const char *)payload;

	GIT_UNUSED(s);

	if (payload == NULL)
		cl_fail("Unexpected path");

	cl_assert_equal_s(expected_path, p);

	return 0;
}