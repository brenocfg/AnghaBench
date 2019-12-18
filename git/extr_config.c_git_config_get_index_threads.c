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
 int /*<<< orphan*/  git_config_get_bool_or_int (char*,int*,int*) ; 
 int git_env_ulong (char*,int /*<<< orphan*/ ) ; 

int git_config_get_index_threads(int *dest)
{
	int is_bool, val;

	val = git_env_ulong("GIT_TEST_INDEX_THREADS", 0);
	if (val) {
		*dest = val;
		return 0;
	}

	if (!git_config_get_bool_or_int("index.threads", &is_bool, &val)) {
		if (is_bool)
			*dest = val ? 0 : 1;
		else
			*dest = val;
		return 0;
	}

	return 1;
}