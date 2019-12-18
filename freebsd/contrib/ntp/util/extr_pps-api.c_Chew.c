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
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*) ; 

void
Chew(struct timespec *tsa, struct timespec *tsc, unsigned sa, unsigned sc)
{
	static int idx;
	struct timespec ts;

	printf("%d.%09d ", tsa->tv_sec, tsa->tv_nsec);
	printf("%d.%09d ", tsc->tv_sec, tsc->tv_nsec);
	printf("%u %u ", sa, sc);

	ts = *tsc;
	timespecsub(&ts,tsa);
	printf("%.9f ", ts.tv_sec + ts.tv_nsec / 1e9);
	printf("\n");
	fflush(stdout);
}