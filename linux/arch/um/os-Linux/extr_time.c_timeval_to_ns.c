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
struct timeval {long long tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 long long UM_NSEC_PER_SEC ; 
 long long UM_NSEC_PER_USEC ; 

__attribute__((used)) static inline long long timeval_to_ns(const struct timeval *tv)
{
	return ((long long) tv->tv_sec * UM_NSEC_PER_SEC) +
		tv->tv_usec * UM_NSEC_PER_USEC;
}