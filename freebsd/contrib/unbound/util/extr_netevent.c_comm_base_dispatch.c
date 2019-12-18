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
struct comm_base {TYPE_1__* eb; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int ub_event_base_dispatch (int /*<<< orphan*/ ) ; 

void 
comm_base_dispatch(struct comm_base* b)
{
	int retval;
	retval = ub_event_base_dispatch(b->eb->base);
	if(retval < 0) {
		fatal_exit("event_dispatch returned error %d, "
			"errno is %s", retval, strerror(errno));
	}
}