#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* hwd; } ;
struct TYPE_3__ {scalar_t__ hwd_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int numthreads ; 
 TYPE_2__* statep ; 

__attribute__((used)) static void
signal_barrier_wakeup(void)
{
	int i;

	for (i = 0; i < numthreads; i++) {
		if (statep->hwd[i].hwd_pid != 0)
			kill(statep->hwd[i].hwd_pid, SIGHUP);
	}
}