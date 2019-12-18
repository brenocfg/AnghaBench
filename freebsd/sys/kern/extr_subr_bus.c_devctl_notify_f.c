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
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  devctl_queue_data_f (char*,int) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 

void
devctl_notify_f(const char *system, const char *subsystem, const char *type,
    const char *data, int flags)
{
	int len = 0;
	char *msg;

	if (system == NULL)
		return;		/* BOGUS!  Must specify system. */
	if (subsystem == NULL)
		return;		/* BOGUS!  Must specify subsystem. */
	if (type == NULL)
		return;		/* BOGUS!  Must specify type. */
	len += strlen(" system=") + strlen(system);
	len += strlen(" subsystem=") + strlen(subsystem);
	len += strlen(" type=") + strlen(type);
	/* add in the data message plus newline. */
	if (data != NULL)
		len += strlen(data);
	len += 3;	/* '!', '\n', and NUL */
	msg = malloc(len, M_BUS, flags);
	if (msg == NULL)
		return;		/* Drop it on the floor */
	if (data != NULL)
		snprintf(msg, len, "!system=%s subsystem=%s type=%s %s\n",
		    system, subsystem, type, data);
	else
		snprintf(msg, len, "!system=%s subsystem=%s type=%s\n",
		    system, subsystem, type);
	devctl_queue_data_f(msg, flags);
}