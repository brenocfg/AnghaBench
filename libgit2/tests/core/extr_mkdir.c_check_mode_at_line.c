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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  clar__assert_equal (char const*,int,char*,int,char*,int,int) ; 

__attribute__((used)) static void check_mode_at_line(
	mode_t expected, mode_t actual, const char *file, int line)
{
	/* FAT filesystems don't support exec bit, nor group/world bits */
	if (!cl_is_chmod_supported()) {
		expected &= 0600;
		actual &= 0600;
	}

	clar__assert_equal(
		file, line, "expected_mode != actual_mode", 1,
		"%07o", (int)expected, (int)(actual & 0777));
}