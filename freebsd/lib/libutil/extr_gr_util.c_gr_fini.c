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
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ initialized ; 
 int lockfd ; 
 char* tempname ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
gr_fini(void)
{
	int serrno;

	if (!initialized)
		return;
	initialized = 0;
	serrno = errno;
	if (*tempname != '\0') {
		unlink(tempname);
		*tempname = '\0';
	}
	if (lockfd != -1)
		close(lockfd);
	errno = serrno;
}