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
struct enum_type {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct enum_type* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct enum_type*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct enum_type *
snmp_enumtc_init(char *name)
{
	struct enum_type *enum_tc;

	if ((enum_tc = calloc(1, sizeof(struct enum_type))) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		return (NULL);
	}

	if ((enum_tc->name = strdup(name)) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		free(enum_tc);
		return (NULL);
	}

	return (enum_tc);
}