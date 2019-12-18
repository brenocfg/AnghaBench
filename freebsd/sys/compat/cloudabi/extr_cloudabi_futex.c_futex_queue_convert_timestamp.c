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
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
typedef  scalar_t__ cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;

/* Variables and functions */
 int cloudabi_clock_time_get (struct thread*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  futex_queue_convert_timestamp_relative (scalar_t__) ; 

__attribute__((used)) static int
futex_queue_convert_timestamp(struct thread *td, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t timeout, cloudabi_timestamp_t precision,
    sbintime_t *sbttimeout, sbintime_t *sbtprecision, bool abstime)
{
	cloudabi_timestamp_t now;
	int error;

	if (abstime) {
		/* Make the time relative. */
		error = cloudabi_clock_time_get(td, clock_id, &now);
		if (error != 0)
			return (error);
		timeout = timeout < now ? 0 : timeout - now;
	}

	*sbttimeout = futex_queue_convert_timestamp_relative(timeout);
	*sbtprecision = futex_queue_convert_timestamp_relative(precision);
	return (0);
}