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
typedef  int uint64_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int HYPERV_TIMER_FREQ ; 
 int HYPERV_TIMER_NS_FACTOR ; 
 struct timespec sbttots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint64_t
hyperv_sbintime2count(sbintime_t time)
{
	struct timespec val;

	val = sbttots(time);
	return (val.tv_sec * HYPERV_TIMER_FREQ) +
	    (val.tv_nsec / HYPERV_TIMER_NS_FACTOR);
}