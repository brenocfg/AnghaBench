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
typedef  int sbintime_t ;
typedef  int cloudabi_timestamp_t ;

/* Variables and functions */
 int INT32_MAX ; 
 int INT64_MAX ; 

__attribute__((used)) static sbintime_t
futex_queue_convert_timestamp_relative(cloudabi_timestamp_t ts)
{
	cloudabi_timestamp_t s, ns;

	s = ts / 1000000000;
	ns = ts % 1000000000;
	if (s > INT32_MAX)
		return (INT64_MAX);
	return ((s << 32) + (ns << 32) / 1000000000);
}