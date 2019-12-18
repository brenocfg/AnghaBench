#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long long uint64_t ;
struct TYPE_6__ {long long tv_sec; long long tv_nsec; } ;
struct TYPE_5__ {long long tv_sec; long long tv_nsec; } ;
struct TYPE_4__ {long long tv_sec; long long tv_nsec; } ;
struct cryptotstat {long long count; TYPE_3__ max; TYPE_2__ min; TYPE_1__ acc; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,long long,long long,long long,long long) ; 

__attribute__((used)) static void
printt(const char* tag, struct cryptotstat *ts)
{
	uint64_t avg, min, max;

	if (ts->count == 0)
		return;
	avg = (1000000000LL*ts->acc.tv_sec + ts->acc.tv_nsec) / ts->count;
	min = 1000000000LL*ts->min.tv_sec + ts->min.tv_nsec;
	max = 1000000000LL*ts->max.tv_sec + ts->max.tv_nsec;
	printf("%16.16s: avg %6llu ns : min %6llu ns : max %7llu ns [%u samps]\n",
		tag, avg, min, max, ts->count);
}