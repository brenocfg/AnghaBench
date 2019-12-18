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
 int /*<<< orphan*/  OSM_DEFAULT_QOS_HIGH_LIMIT ; 
 int /*<<< orphan*/  log_report (char*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subn_verify_high_limit(int *high_limit, const char *prefix)
{
	if (*high_limit < 0 || *high_limit > 255) {
		if (*high_limit > 255)
			log_report(" Invalid Cached Option: %s_high_limit=%d: "
				   "Using Default: %d\n",
				   prefix, *high_limit,
				   OSM_DEFAULT_QOS_HIGH_LIMIT);
		*high_limit = -1;
	}
}