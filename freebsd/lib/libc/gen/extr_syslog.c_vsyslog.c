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
 int /*<<< orphan*/  THREAD_LOCK () ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog_cancel_cleanup ; 
 int /*<<< orphan*/  vsyslog1 (int,char const*,int /*<<< orphan*/ ) ; 

void
vsyslog(int pri, const char *fmt, va_list ap)
{

	THREAD_LOCK();
	pthread_cleanup_push(syslog_cancel_cleanup, NULL);
	vsyslog1(pri, fmt, ap);
	pthread_cleanup_pop(1);
}