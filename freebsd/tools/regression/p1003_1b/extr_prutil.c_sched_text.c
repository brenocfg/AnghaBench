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

/* Variables and functions */
#define  SCHED_FIFO 130 
#define  SCHED_OTHER 129 
#define  SCHED_RR 128 

char *sched_text(int scheduler)
{
	switch(scheduler)
	{
		case SCHED_FIFO:
		return "SCHED_FIFO";

		case SCHED_RR:
		return "SCHED_RR";

		case SCHED_OTHER:
		return "SCHED_OTHER";

		default:
		return "Illegal scheduler value";
	}
}