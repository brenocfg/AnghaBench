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
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int int_array_len (int*) ; 
 int /*<<< orphan*/  int_array_sort_unique (int*) ; 
 scalar_t__ os_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int int_array_tests(void)
{
	int test1[] = { 1, 2, 3, 4, 5, 6, 0 };
	int test2[] = { 1, -1, 0 };
	int test3[] = { 1, 1, 1, -1, 2, 3, 4, 1, 2, 0 };
	int test3_res[] = { -1, 1, 2, 3, 4, 0 };
	int errors = 0;
	int len;

	wpa_printf(MSG_INFO, "int_array tests");

	if (int_array_len(test1) != 6 ||
	    int_array_len(test2) != 2)
		errors++;

	int_array_sort_unique(test3);
	len = int_array_len(test3_res);
	if (int_array_len(test3) != len)
		errors++;
	else if (os_memcmp(test3, test3_res, len * sizeof(int)) != 0)
		errors++;

	if (errors) {
		wpa_printf(MSG_ERROR, "%d int_array test(s) failed", errors);
		return -1;
	}

	return 0;
}