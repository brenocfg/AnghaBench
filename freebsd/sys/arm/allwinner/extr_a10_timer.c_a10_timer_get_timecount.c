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
typedef  int /*<<< orphan*/  u_int ;
struct timecounter {int /*<<< orphan*/ * tc_priv; } ;

/* Variables and functions */
 scalar_t__ timer_read_counter64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
a10_timer_get_timecount(struct timecounter *tc)
{

	if (tc->tc_priv == NULL)
		return (0);

	return ((u_int)timer_read_counter64(tc->tc_priv));
}