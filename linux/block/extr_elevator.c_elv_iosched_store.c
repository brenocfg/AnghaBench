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
struct request_queue {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int __elevator_change (struct request_queue*,char const*) ; 
 int /*<<< orphan*/  elv_support_iosched (struct request_queue*) ; 
 int /*<<< orphan*/  queue_is_mq (struct request_queue*) ; 

ssize_t elv_iosched_store(struct request_queue *q, const char *name,
			  size_t count)
{
	int ret;

	if (!queue_is_mq(q) || !elv_support_iosched(q))
		return count;

	ret = __elevator_change(q, name);
	if (!ret)
		return count;

	return ret;
}