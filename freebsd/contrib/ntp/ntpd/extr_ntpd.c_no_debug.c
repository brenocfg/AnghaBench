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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int errno ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static RETSIGTYPE
no_debug(
	int sig
	)
{
	int saved_errno = errno;

	msyslog(LOG_DEBUG, "ntpd not compiled for debugging (signal %d)", sig);
	errno = saved_errno;
}