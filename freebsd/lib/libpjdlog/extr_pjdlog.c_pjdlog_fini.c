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
 scalar_t__ PJDLOG_INITIALIZED ; 
 scalar_t__ PJDLOG_MODE_SYSLOG ; 
 scalar_t__ PJDLOG_NOT_INITIALIZED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closelog () ; 
 int errno ; 
 scalar_t__ pjdlog_initialized ; 
 scalar_t__ pjdlog_mode ; 
 int pjdlog_sock ; 

void
pjdlog_fini(void)
{
	int saved_errno;

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);

	saved_errno = errno;

	if (pjdlog_mode == PJDLOG_MODE_SYSLOG)
		closelog();

	pjdlog_initialized = PJDLOG_NOT_INITIALIZED;
	pjdlog_sock = -1;

	errno = saved_errno;
}