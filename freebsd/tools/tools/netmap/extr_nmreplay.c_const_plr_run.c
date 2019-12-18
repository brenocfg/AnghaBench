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
typedef  scalar_t__ uint64_t ;
struct _qs {int cur_drop; } ;
struct _cfg {scalar_t__* d; } ;

/* Variables and functions */
 scalar_t__ my_random24 () ; 

__attribute__((used)) static int
const_plr_run(struct _qs *q, struct _cfg *arg)
{
	(void)arg;
	uint64_t r = my_random24();
	q->cur_drop = r < arg->d[0];
#if 1	/* keep stats */
	arg->d[1]++;
	arg->d[2] += q->cur_drop;
#endif
	return 0;
}