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
typedef  struct timeval {long tv_sec; long tv_usec; } const timeval ;
typedef  long int64_t ;

/* Variables and functions */
 int const PCAP_TSTAMP_PRECISION_NANO ; 
 long const _NSEC_PER_SEC ; 

__attribute__((used)) static inline
struct timeval
snf_timestamp_to_timeval(const int64_t ts_nanosec, const int tstamp_precision)
{
	struct timeval tv;
	long tv_nsec;
        const static struct timeval zero_timeval;

        if (ts_nanosec == 0)
                return zero_timeval;

	tv.tv_sec = ts_nanosec / _NSEC_PER_SEC;
	tv_nsec = (ts_nanosec % _NSEC_PER_SEC);

	/* libpcap expects tv_usec to be nanos if using nanosecond precision. */
	if (tstamp_precision == PCAP_TSTAMP_PRECISION_NANO)
		tv.tv_usec = tv_nsec;
	else
		tv.tv_usec = tv_nsec / 1000;

	return tv;
}