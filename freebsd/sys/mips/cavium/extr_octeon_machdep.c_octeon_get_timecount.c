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
 scalar_t__ octeon_get_ticks () ; 

__attribute__((used)) static unsigned
octeon_get_timecount(struct timecounter *tc)
{
	return ((unsigned)octeon_get_ticks());
}