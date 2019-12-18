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
typedef  int /*<<< orphan*/ * pthread_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUCLOCK_WHICH_TID ; 
 int EINVAL ; 
 int /*<<< orphan*/  TID (int /*<<< orphan*/ *) ; 
 scalar_t__ clock_getcpuclockid2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 

int
_pthread_getcpuclockid(pthread_t pthread, clockid_t *clock_id)
{

	if (pthread == NULL)
		return (EINVAL);

	if (clock_getcpuclockid2(TID(pthread), CPUCLOCK_WHICH_TID, clock_id))
		return (errno);
	return (0);
}