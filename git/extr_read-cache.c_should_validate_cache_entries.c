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
 scalar_t__ getenv (char*) ; 

int should_validate_cache_entries(void)
{
	static int validate_index_cache_entries = -1;

	if (validate_index_cache_entries < 0) {
		if (getenv("GIT_TEST_VALIDATE_INDEX_CACHE_ENTRIES"))
			validate_index_cache_entries = 1;
		else
			validate_index_cache_entries = 0;
	}

	return validate_index_cache_entries;
}