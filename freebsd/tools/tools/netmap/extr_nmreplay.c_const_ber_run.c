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
typedef  scalar_t__ uint32_t ;
struct _qs {int cur_len; int cur_drop; } ;
struct _cfg {int* d; scalar_t__* arg; } ;

/* Variables and functions */
 int MAX_PKT ; 
 int /*<<< orphan*/  RD (int,char*,int,int) ; 
 scalar_t__ my_random24 () ; 

__attribute__((used)) static int
const_ber_run(struct _qs *q, struct _cfg *arg)
{
	int l = q->cur_len;
	uint64_t r = my_random24();
	uint32_t *plr = arg->arg;

	if (l >= MAX_PKT) {
		RD(5, "pkt len %d too large, trim to %d", l, MAX_PKT-1);
		l = MAX_PKT-1;
	}
	q->cur_drop = r < plr[l];
#if 1	/* keep stats */
	arg->d[1] += l * 8;
	arg->d[2] += q->cur_drop;
#endif
	return 0;
}