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
typedef  int uint32_t ;

/* Variables and functions */
 int MS_IN_USEC ; 
 int USECS_IN_SECOND ; 

__attribute__((used)) static uint32_t
bbr_ts_convert(uint32_t cts) {
	uint32_t sec, msec;

	sec = cts / MS_IN_USEC;
	msec = cts - (MS_IN_USEC * sec);
	return ((sec * USECS_IN_SECOND) + (msec * MS_IN_USEC));
}