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
struct elevator_queue {struct bfq_data* elevator_data; } ;
struct bfq_data {scalar_t__ low_latency; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_end_wr (struct bfq_data*) ; 
 int bfq_var_store (unsigned long*,char const*) ; 

__attribute__((used)) static ssize_t bfq_low_latency_store(struct elevator_queue *e,
				     const char *page, size_t count)
{
	struct bfq_data *bfqd = e->elevator_data;
	unsigned long __data;
	int ret;

	ret = bfq_var_store(&__data, (page));
	if (ret)
		return ret;

	if (__data > 1)
		__data = 1;
	if (__data == 0 && bfqd->low_latency != 0)
		bfq_end_wr(bfqd);
	bfqd->low_latency = __data;

	return count;
}