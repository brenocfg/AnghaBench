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
struct timeval {int dummy; } ;
struct event_base {struct common_timeout_list** common_timeout_queues; } ;
struct common_timeout_list {int dummy; } ;

/* Variables and functions */
 size_t COMMON_TIMEOUT_IDX (struct timeval const*) ; 

__attribute__((used)) static inline struct common_timeout_list *
get_common_timeout_list(struct event_base *base, const struct timeval *tv)
{
	return base->common_timeout_queues[COMMON_TIMEOUT_IDX(tv)];
}