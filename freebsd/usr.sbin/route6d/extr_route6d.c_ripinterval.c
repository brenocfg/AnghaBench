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
 double RAND_MAX ; 
 int RIPRANDDEV ; 
 int interval ; 
 scalar_t__ nextalarm ; 
 double rand () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ripinterval(int timer)
{
	double r = rand();

	interval = (int)(timer + timer * RIPRANDDEV * (r / RAND_MAX - 0.5));
	nextalarm = time(NULL) + interval;
	return interval;
}