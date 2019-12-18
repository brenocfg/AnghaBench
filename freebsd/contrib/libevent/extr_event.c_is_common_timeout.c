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
struct timeval {int tv_usec; } ;
struct event_base {int n_common_timeouts; } ;

/* Variables and functions */
 int COMMON_TIMEOUT_IDX (struct timeval const*) ; 
 int COMMON_TIMEOUT_MAGIC ; 
 int COMMON_TIMEOUT_MASK ; 

__attribute__((used)) static inline int
is_common_timeout(const struct timeval *tv,
    const struct event_base *base)
{
	int idx;
	if ((tv->tv_usec & COMMON_TIMEOUT_MASK) != COMMON_TIMEOUT_MAGIC)
		return 0;
	idx = COMMON_TIMEOUT_IDX(tv);
	return idx < base->n_common_timeouts;
}