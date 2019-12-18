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
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ERR_MSG ; 
 int /*<<< orphan*/  DeregisterEventSource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTLOG_ERROR_TYPE ; 
 int /*<<< orphan*/ * RegisterEventSource (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ReportEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

void
NTReportError(const char *name, const char *str) {
	HANDLE hNTAppLog = NULL;
	const char *buf[1];

	buf[0] = str;

	hNTAppLog = RegisterEventSource(NULL, name);

	ReportEvent(hNTAppLog, EVENTLOG_ERROR_TYPE, 0,
		    BIND_ERR_MSG, NULL, 1, 0, buf, NULL);

	DeregisterEventSource(hNTAppLog);
}