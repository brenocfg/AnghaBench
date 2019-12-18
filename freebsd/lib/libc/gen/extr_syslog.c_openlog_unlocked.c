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
 int LOG_FACMASK ; 
 int LOG_NDELAY ; 
 int LogFacility ; 
 int LogStat ; 
 char const* LogTag ; 
 int /*<<< orphan*/  connectlog () ; 
 int opened ; 

__attribute__((used)) static void
openlog_unlocked(const char *ident, int logstat, int logfac)
{
	if (ident != NULL)
		LogTag = ident;
	LogStat = logstat;
	if (logfac != 0 && (logfac &~ LOG_FACMASK) == 0)
		LogFacility = logfac;

	if (LogStat & LOG_NDELAY)	/* open immediately */
		connectlog();

	opened = 1;	/* ident and facility has been set */
}