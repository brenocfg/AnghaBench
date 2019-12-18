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
struct _qs {unsigned long long cur_tt; int cur_len; } ;
struct _cfg {int* d; } ;

/* Variables and functions */
 unsigned long long TIME_UNITS ; 

__attribute__((used)) static int
ether_bw_run(struct _qs *q, struct _cfg *arg)
{
	uint64_t bps = arg->d[0];
	q->cur_tt = bps ? 8ULL * TIME_UNITS * (q->cur_len + 24) / bps : 0 ;
	return 0;
}