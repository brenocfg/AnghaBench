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
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ RegisterEventSourceA (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ ms_eventlog ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void openlog(const char *ident, int logopt, int facility)
{
	if (ms_eventlog)
		return;

	ms_eventlog = RegisterEventSourceA(NULL, ident);

	if (!ms_eventlog)
		warning("RegisterEventSource() failed: %lu", GetLastError());
}