#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long tv_nsec; scalar_t__ tv_sec; } ;
struct ksched {TYPE_1__ rr_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_P31B ; 
 int /*<<< orphan*/  M_WAITOK ; 
 long hz ; 
 struct ksched* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long sched_rr_interval () ; 

int
ksched_attach(struct ksched **p)
{
	struct ksched *ksched;

	ksched = malloc(sizeof(*ksched), M_P31B, M_WAITOK);
	ksched->rr_interval.tv_sec = 0;
	ksched->rr_interval.tv_nsec = 1000000000L / hz * sched_rr_interval();
	*p = ksched;
	return (0);
}