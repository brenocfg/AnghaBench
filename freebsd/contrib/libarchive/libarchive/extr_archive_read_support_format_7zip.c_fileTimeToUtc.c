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
typedef  int uint64_t ;
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int EPOC_TIME ; 

__attribute__((used)) static void
fileTimeToUtc(uint64_t fileTime, time_t *timep, long *ns)
{

	if (fileTime >= EPOC_TIME) {
		fileTime -= EPOC_TIME;
		/* milli seconds base */
		*timep = (time_t)(fileTime / 10000000);
		/* nano seconds base */
		*ns = (long)(fileTime % 10000000) * 100;
	} else {
		*timep = 0;
		*ns = 0;
	}
}