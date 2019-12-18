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
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

unsigned long elapsed_ms(struct timeval* now, struct timeval* prev) {
	unsigned long elapsed = 0;

	if (now->tv_sec > prev->tv_sec)
		elapsed = 1000*1000 - prev->tv_usec +
			  now->tv_usec;
	else {
		assert(now->tv_sec == prev->tv_sec);
		elapsed = now->tv_usec - prev->tv_usec;
	}	
	elapsed /= 1000; //ms

	elapsed += (now->tv_sec - prev->tv_sec)*1000;
	return elapsed;
}