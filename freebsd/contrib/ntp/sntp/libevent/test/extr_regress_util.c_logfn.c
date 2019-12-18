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
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ logmsg ; 
 int logsev ; 
 scalar_t__ strdup (char const*) ; 
 int /*<<< orphan*/  tt_want (char const*) ; 

__attribute__((used)) static void
logfn(int severity, const char *msg)
{
	logsev = severity;
	tt_want(msg);
	if (msg) {
		if (logmsg)
			free(logmsg);
		logmsg = strdup(msg);
	}
}