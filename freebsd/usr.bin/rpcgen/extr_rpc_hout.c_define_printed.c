#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* procs; struct TYPE_5__* next; } ;
typedef  TYPE_1__ version_list ;
struct TYPE_6__ {int /*<<< orphan*/  proc_name; struct TYPE_6__* next; } ;
typedef  TYPE_2__ proc_list ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
define_printed(proc_list *stop, version_list *start)
{
	version_list *vers;
	proc_list *proc;

	for (vers = start; vers != NULL; vers = vers->next) {
		for (proc = vers->procs; proc != NULL; proc = proc->next) {
			if (proc == stop) {
				return (0);
			} else if (streq(proc->proc_name, stop->proc_name)) {
				return (1);
			}
		}
	}
	abort();
	/* NOTREACHED */
}