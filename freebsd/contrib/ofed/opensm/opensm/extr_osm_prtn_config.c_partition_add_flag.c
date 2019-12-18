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
struct part_conf {int is_ipoib; int /*<<< orphan*/  p_log; int /*<<< orphan*/  indx0; int /*<<< orphan*/  membership; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  FULL ; 
 int /*<<< orphan*/  LIMITED ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ parse_group_flag (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int partition_add_flag(unsigned lineno, struct part_conf *conf,
			      char *flag, char *val)
{
	int len = strlen(flag);

	/* ipoib gc group flags are processed here. */
	if (parse_group_flag(lineno, conf->p_log, &conf->flags, flag, val))
		return 0;

	/* partition flags go here. */
	if (!strncmp(flag, "ipoib", len)) {
		conf->is_ipoib = 1;
	} else if (!strncmp(flag, "defmember", len)) {
		if (!val || (strncmp(val, "limited", strlen(val))
			     && strncmp(val, "both", strlen(val))
			     && strncmp(val, "full", strlen(val))))
			OSM_LOG(conf->p_log, OSM_LOG_VERBOSE,
				"PARSE WARN: line %d: "
				"flag \'defmember\' requires valid value (limited or full or both)"
				" - skipped\n", lineno);
		else {
			if (!strncmp(val, "full", strlen(val)))
				conf->membership = FULL;
			else if (!strncmp(val, "both", strlen(val)))
				conf->membership = BOTH;
			else
				conf->membership = LIMITED;
		}
	} else if (!strcmp(flag, "indx0"))
		conf->indx0 = TRUE;
	else {
		OSM_LOG(conf->p_log, OSM_LOG_VERBOSE,
			"PARSE WARN: line %d: "
			"unrecognized partition flag \'%s\'"
			" - ignored\n", lineno, flag);
	}
	return 0;
}