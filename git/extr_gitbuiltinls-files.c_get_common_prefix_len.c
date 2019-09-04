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
 int strlen (char const*) ; 

__attribute__((used)) static int get_common_prefix_len(const char *common_prefix)
{
	int common_prefix_len;

	if (!common_prefix)
		return 0;

	common_prefix_len = strlen(common_prefix);

	/*
	 * If the prefix has a trailing slash, strip it so that submodules wont
	 * be pruned from the index.
	 */
	if (common_prefix[common_prefix_len - 1] == '/')
		common_prefix_len--;

	return common_prefix_len;
}