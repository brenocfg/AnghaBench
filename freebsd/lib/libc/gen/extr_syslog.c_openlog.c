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
 int /*<<< orphan*/  THREAD_LOCK () ; 
 int /*<<< orphan*/  openlog_unlocked (char const*,int,int) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog_cancel_cleanup ; 

void
openlog(const char *ident, int logstat, int logfac)
{

	THREAD_LOCK();
	pthread_cleanup_push(syslog_cancel_cleanup, NULL);
	openlog_unlocked(ident, logstat, logfac);
	pthread_cleanup_pop(1);
}