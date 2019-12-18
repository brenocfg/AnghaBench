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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,char*) ; 
 scalar_t__ ve_utc ; 

void
ve_utc_set(time_t utc)
{
	if (utc > ve_utc) {
		DEBUG_PRINTF(2, ("Set ve_utc=%jd\n", (intmax_t)utc));
		ve_utc = utc;
	}
}