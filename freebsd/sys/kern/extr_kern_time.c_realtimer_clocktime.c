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
struct timespec {int dummy; } ;
typedef  scalar_t__ clockid_t ;

/* Variables and functions */
 scalar_t__ CLOCK_REALTIME ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 

__attribute__((used)) static void
realtimer_clocktime(clockid_t id, struct timespec *ts)
{
	if (id == CLOCK_REALTIME)
		getnanotime(ts);
	else	/* CLOCK_MONOTONIC */
		getnanouptime(ts);
}