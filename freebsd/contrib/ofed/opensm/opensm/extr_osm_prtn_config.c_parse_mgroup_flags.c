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
struct precreate_mgroup {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  osm_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  parse_group_flag (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int parse_name_token (char*,char**,char**) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int parse_mgroup_flags(osm_log_t * p_log,
				struct precreate_mgroup *mgroup,
				char *p, unsigned lineno)
{
	int ret, len = 0;
	char *flag, *val, *q;
	do {
		flag = val = NULL;
		q = strchr(p, ',');
		if (q)
			*q++ = '\0';

		ret = parse_name_token(p, &flag, &val);

		if (!parse_group_flag(lineno, p_log, &mgroup->flags,
				     flag, val)) {
			OSM_LOG(p_log, OSM_LOG_VERBOSE,
				"PARSE WARN: line %d: "
				"unrecognized mgroup flag \'%s\'"
				" - ignored\n", lineno, flag);
		}
		p += ret;
		len += ret;
	} while (q);

	return (len);
}