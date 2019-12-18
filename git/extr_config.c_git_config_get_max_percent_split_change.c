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
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int*) ; 

int git_config_get_max_percent_split_change(void)
{
	int val = -1;

	if (!git_config_get_int("splitindex.maxpercentchange", &val)) {
		if (0 <= val && val <= 100)
			return val;

		return error(_("splitIndex.maxPercentChange value '%d' "
			       "should be between 0 and 100"), val);
	}

	return -1; /* default value */
}