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
typedef  int /*<<< orphan*/  time_t ;
struct timeval {int dummy; } ;
struct comm_base {TYPE_1__* eb; } ;
struct TYPE_2__ {struct timeval now; int /*<<< orphan*/  secs; } ;

/* Variables and functions */

void 
comm_base_timept(struct comm_base* b, time_t** tt, struct timeval** tv)
{
	*tt = &b->eb->secs;
	*tv = &b->eb->now;
}