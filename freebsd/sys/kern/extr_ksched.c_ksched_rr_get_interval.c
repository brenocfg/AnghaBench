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
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct ksched {struct timespec rr_interval; } ;

/* Variables and functions */

int
ksched_rr_get_interval(struct ksched *ksched, struct thread *td,
    struct timespec *timespec)
{

	*timespec = ksched->rr_interval;
	return (0);
}