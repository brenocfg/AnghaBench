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
struct timecounter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTIMER_CLO ; 
 int /*<<< orphan*/ * bcm_systimer_sc ; 
 int bcm_systimer_tc_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
bcm_systimer_tc_get_timecount(struct timecounter *tc)
{
	if (bcm_systimer_sc == NULL)
		return (0);

	return bcm_systimer_tc_read_4(SYSTIMER_CLO);
}