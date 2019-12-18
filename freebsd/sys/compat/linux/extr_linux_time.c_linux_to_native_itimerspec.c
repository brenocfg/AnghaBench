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
struct l_itimerspec {int /*<<< orphan*/  it_value; int /*<<< orphan*/  it_interval; } ;
struct itimerspec {int /*<<< orphan*/  it_value; int /*<<< orphan*/  it_interval; } ;

/* Variables and functions */
 int linux_to_native_timespec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
linux_to_native_itimerspec(struct itimerspec *ntp, struct l_itimerspec *ltp)
{
	int error;

	error = linux_to_native_timespec(&ntp->it_interval, &ltp->it_interval);
	if (error == 0)
		error = linux_to_native_timespec(&ntp->it_value, &ltp->it_value);
	return (error);
}