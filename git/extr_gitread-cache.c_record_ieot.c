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
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int /*<<< orphan*/  git_config_get_index_threads (int*) ; 

__attribute__((used)) static int record_ieot(void)
{
	int val;

	if (!git_config_get_bool("index.recordoffsettable", &val))
		return val;

	/*
	 * As a convenience, the offset table used for threading is
	 * written by default if the user explicitly requested
	 * threaded index reads.
	 */
	return !git_config_get_index_threads(&val) && val != 1;
}