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
struct parallel_processes {int max_processes; TYPE_2__* children; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {scalar_t__ state; TYPE_1__ process; } ;

/* Variables and functions */
 scalar_t__ GIT_CP_WORKING ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kill_children(struct parallel_processes *pp, int signo)
{
	int i, n = pp->max_processes;

	for (i = 0; i < n; i++)
		if (pp->children[i].state == GIT_CP_WORKING)
			kill(pp->children[i].process.pid, signo);
}