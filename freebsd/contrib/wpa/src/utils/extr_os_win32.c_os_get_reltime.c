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
struct os_time {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
struct os_reltime {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int os_get_time (struct os_time*) ; 

int os_get_reltime(struct os_reltime *t)
{
	/* consider using performance counters or so instead */
	struct os_time now;
	int res = os_get_time(&now);
	t->sec = now.sec;
	t->usec = now.usec;
	return res;
}