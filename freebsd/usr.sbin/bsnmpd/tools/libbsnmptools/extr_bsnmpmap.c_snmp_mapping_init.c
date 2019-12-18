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
struct snmp_mappings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct snmp_mappings* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct snmp_mappings *
snmp_mapping_init(void)
{
	struct snmp_mappings *m;

	if ((m = calloc(1, sizeof(struct snmp_mappings))) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		return (NULL);
	}

	return (m);
}