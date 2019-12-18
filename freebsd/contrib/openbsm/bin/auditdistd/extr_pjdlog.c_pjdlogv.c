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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int LOG_ALERT ; 
 int LOG_CRIT ; 
 int LOG_EMERG ; 
 int LOG_ERR ; 
 int LOG_INFO ; 
 int LOG_NOTICE ; 
 int LOG_WARNING ; 
 scalar_t__ PJDLOG_INITIALIZED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pjdlog_initialized ; 
 int /*<<< orphan*/  pjdlogv_common (int,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 

void
pjdlogv(int loglevel, const char *fmt, va_list ap)
{

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);

	/* LOG_DEBUG is invalid here, pjdlogv?_debug() should be used. */
	assert(loglevel == LOG_EMERG || loglevel == LOG_ALERT ||
	    loglevel == LOG_CRIT || loglevel == LOG_ERR ||
	    loglevel == LOG_WARNING || loglevel == LOG_NOTICE ||
	    loglevel == LOG_INFO);

	pjdlogv_common(loglevel, 0, -1, fmt, ap);
}