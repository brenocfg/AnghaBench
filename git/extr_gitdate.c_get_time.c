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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_time(struct timeval *now)
{
	const char *x;

	x = getenv("GIT_TEST_DATE_NOW");
	if (x) {
		now->tv_sec = atoi(x);
		now->tv_usec = 0;
	}
	else
		gettimeofday(now, NULL);
}