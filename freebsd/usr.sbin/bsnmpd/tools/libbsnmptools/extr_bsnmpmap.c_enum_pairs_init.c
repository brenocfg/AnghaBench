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
struct enum_pairs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  STAILQ_INIT (struct enum_pairs*) ; 
 int /*<<< orphan*/  errno ; 
 struct enum_pairs* malloc (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct enum_pairs *
enum_pairs_init(void)
{
	struct enum_pairs *snmp_enum;

	if ((snmp_enum = malloc(sizeof(struct enum_pairs))) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		return (NULL);
	}

	STAILQ_INIT(snmp_enum);
	return (snmp_enum);
}