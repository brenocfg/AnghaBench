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
struct clocktime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_print_ct (struct clocktime*,int) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec const*,struct clocktime*) ; 

void
clock_print_ts(const struct timespec *ts, int nsdigits)
{
	struct clocktime ct;

	clock_ts_to_ct(ts, &ct);
	clock_print_ct(&ct, nsdigits);
}