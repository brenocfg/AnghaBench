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
struct _qs {int cur_delay; } ;
struct _cfg {int* d; } ;

/* Variables and functions */
 int my_random24 () ; 

__attribute__((used)) static int
uniform_delay_run(struct _qs *q, struct _cfg *arg)
{
	uint64_t x = my_random24();
	q->cur_delay = arg->d[0] + ((arg->d[2] * x) >> 24);
#if 0 /* COMPUTE_STATS */
#endif /* COMPUTE_STATS */
	return 0;
}