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
struct trapframe {int /*<<< orphan*/ * tf_x; } ;
struct TYPE_5__ {uintptr_t cpu_dtrace_caller; } ;
typedef  TYPE_1__ solaris_cpu_t ;
struct TYPE_6__ {int fbtp_savedval; int /*<<< orphan*/  fbtp_id; scalar_t__ fbtp_patchpoint; struct TYPE_6__* fbtp_hashnext; } ;
typedef  TYPE_2__ fbt_probe_t ;

/* Variables and functions */
 size_t FBT_ADDR2NDX (uintptr_t) ; 
 size_t curcpu ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** fbt_probetab ; 
 TYPE_1__* solaris_cpu ; 

int
fbt_invop(uintptr_t addr, struct trapframe *frame, uintptr_t rval)
{
	solaris_cpu_t *cpu;
	fbt_probe_t *fbt;

	cpu = &solaris_cpu[curcpu];
	fbt = fbt_probetab[FBT_ADDR2NDX(addr)];

	for (; fbt != NULL; fbt = fbt->fbtp_hashnext) {
		if ((uintptr_t)fbt->fbtp_patchpoint == addr) {
			cpu->cpu_dtrace_caller = addr;

			dtrace_probe(fbt->fbtp_id, frame->tf_x[0],
			    frame->tf_x[1], frame->tf_x[2],
			    frame->tf_x[3], frame->tf_x[4]);

			cpu->cpu_dtrace_caller = 0;
			return (fbt->fbtp_savedval);
		}
	}

	return (0);
}