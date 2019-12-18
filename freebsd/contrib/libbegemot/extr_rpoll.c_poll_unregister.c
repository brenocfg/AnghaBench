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
struct TYPE_2__ {int fd; int /*<<< orphan*/ * pfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  poll_blocksig () ; 
 int /*<<< orphan*/  poll_unblocksig () ; 
 int rebuild ; 
 TYPE_1__* regs ; 
 int /*<<< orphan*/  regs_used ; 
 scalar_t__ rpoll_trace ; 
 int /*<<< orphan*/  stderr ; 

void
poll_unregister(int handle)
{
	if(rpoll_trace)
		fprintf(stderr, "poll_unregister(%d)", handle);

	poll_blocksig();

	regs[handle].fd = -1;
# ifdef USE_POLL
	regs[handle].pfd = NULL;
# endif
	rebuild = 1;
	regs_used--;

	poll_unblocksig();
}