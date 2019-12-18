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

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int slowio_pollcnt ; 
 int /*<<< orphan*/  slowio_starttime ; 

void
slowio_start()
{

	/* Delay one in every 8 operations */
	slowio_pollcnt = (slowio_pollcnt + 1) & 7;
	if (slowio_pollcnt == 0) {
		gettimeofday(&slowio_starttime, NULL);
	}
}