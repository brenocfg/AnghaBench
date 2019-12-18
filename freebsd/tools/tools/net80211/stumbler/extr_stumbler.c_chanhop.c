#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {unsigned long tv_sec; unsigned long tv_usec; } ;
struct TYPE_2__ {int chan; int /*<<< orphan*/  last_hop; } ;

/* Variables and functions */
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  die (int,char*) ; 
 unsigned long elapsed_ms (struct timeval*,int /*<<< orphan*/ *) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 unsigned long hopfreq ; 
 int /*<<< orphan*/  set_chan (int) ; 

void chanhop(struct timeval* tv) {
	unsigned long elapsed = 0;

	if (gettimeofday(tv, NULL) == -1)
		die(1, "gettimeofday()");


	elapsed = elapsed_ms(tv, &chaninfo.last_hop);

	// need to chan hop
	if (elapsed >= hopfreq) {
		int c;

		c = chaninfo.chan + 1;

		if (c > 11)
			c = 1;

		set_chan(c);

		elapsed = hopfreq;
	} 
	// how much can we sleep?
	else {
		elapsed = hopfreq - elapsed;
	}

	// ok calculate sleeping time...
	tv->tv_sec = elapsed/1000;
	tv->tv_usec = (elapsed - tv->tv_sec*1000)*1000;
}