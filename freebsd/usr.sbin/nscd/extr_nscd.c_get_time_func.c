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
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 

void
get_time_func(struct timeval *time)
{
	struct timespec res;
	memset(&res, 0, sizeof(struct timespec));
	clock_gettime(CLOCK_MONOTONIC, &res);

	time->tv_sec = res.tv_sec;
	time->tv_usec = 0;
}