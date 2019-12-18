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
typedef  int cloudabi_clockid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_PROCESS_CPUTIME_ID ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  CLOCK_THREAD_CPUTIME_ID ; 
#define  CLOUDABI_CLOCK_MONOTONIC 131 
#define  CLOUDABI_CLOCK_PROCESS_CPUTIME_ID 130 
#define  CLOUDABI_CLOCK_REALTIME 129 
#define  CLOUDABI_CLOCK_THREAD_CPUTIME_ID 128 
 int EINVAL ; 

__attribute__((used)) static int
cloudabi_convert_clockid(cloudabi_clockid_t in, clockid_t *out)
{
	switch (in) {
	case CLOUDABI_CLOCK_MONOTONIC:
		*out = CLOCK_MONOTONIC;
		return (0);
	case CLOUDABI_CLOCK_PROCESS_CPUTIME_ID:
		*out = CLOCK_PROCESS_CPUTIME_ID;
		return (0);
	case CLOUDABI_CLOCK_REALTIME:
		*out = CLOCK_REALTIME;
		return (0);
	case CLOUDABI_CLOCK_THREAD_CPUTIME_ID:
		*out = CLOCK_THREAD_CPUTIME_ID;
		return (0);
	default:
		return (EINVAL);
	}
}