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
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(void)
{
	struct timespec	 timeout;

	timeout.tv_sec = 0;
	timeout.tv_nsec = 100000000;	/* 0.1 seconds */
	
	if (nanosleep(&timeout, NULL)) {
		perror("nanosleep");
		return 1;
	}
	return 0;
}