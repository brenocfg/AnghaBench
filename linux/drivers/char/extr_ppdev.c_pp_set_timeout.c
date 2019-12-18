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
struct pardevice {long timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 long HZ ; 
 long usecs_to_jiffies (int) ; 

__attribute__((used)) static int pp_set_timeout(struct pardevice *pdev, long tv_sec, int tv_usec)
{
	long to_jiffies;

	if ((tv_sec < 0) || (tv_usec < 0))
		return -EINVAL;

	to_jiffies = usecs_to_jiffies(tv_usec);
	to_jiffies += tv_sec * HZ;
	if (to_jiffies <= 0)
		return -EINVAL;

	pdev->timeout = to_jiffies;
	return 0;
}