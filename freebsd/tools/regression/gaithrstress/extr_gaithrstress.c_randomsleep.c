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
struct timespec {double tv_nsec; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ my_arc4random_r () ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
randomsleep(double max_sleep_sec)
{
	struct timespec slptime = { 0, 0 };
	double rndsleep;

	rndsleep = (double)my_arc4random_r() / 4294967296.0 * max_sleep_sec;
	while (rndsleep >= 1.0) {
		slptime.tv_sec++;
		rndsleep -= 1.0;
	}
	slptime.tv_nsec = rndsleep * 1e9;
	(void)nanosleep(&slptime, NULL);
}