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
typedef  int timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int parse_timestamp (char const*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static int process_deepen_since(const char *line, timestamp_t *deepen_since, int *deepen_rev_list)
{
	const char *arg;
	if (skip_prefix(line, "deepen-since ", &arg)) {
		char *end = NULL;
		*deepen_since = parse_timestamp(arg, &end, 0);
		if (!end || *end || !deepen_since ||
		    /* revisions.c's max_age -1 is special */
		    *deepen_since == -1)
			die("Invalid deepen-since: %s", line);
		*deepen_rev_list = 1;
		return 1;
	}
	return 0;
}