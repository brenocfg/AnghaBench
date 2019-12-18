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
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int cloudabi_convert_clockid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cloudabi_convert_timespec (struct timespec*,int /*<<< orphan*/ *) ; 
 int kern_clock_gettime (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 

int
cloudabi_clock_time_get(struct thread *td, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t *ret)
{
	struct timespec ts;
	int error;
	clockid_t clockid;

	error = cloudabi_convert_clockid(clock_id, &clockid);
	if (error != 0)
		return (error);
	error = kern_clock_gettime(td, clockid, &ts);
	if (error != 0)
		return (error);
	return (cloudabi_convert_timespec(&ts, ret));
}