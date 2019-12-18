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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal_want_message ; 
 scalar_t__ fatal_want_severity ; 
 int /*<<< orphan*/  logmsg ; 
 scalar_t__ logsev ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fatalfn(int exitcode)
{
	if (logsev != fatal_want_severity ||
	    !logmsg ||
	    strcmp(logmsg, fatal_want_message))
		exit(0);
	else
		exit(exitcode);
}