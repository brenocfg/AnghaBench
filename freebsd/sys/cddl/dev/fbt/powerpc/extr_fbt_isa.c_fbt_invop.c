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
struct trapframe {uintptr_t* fixreg; uintptr_t srr0; } ;
struct TYPE_5__ {uintptr_t cpu_dtrace_caller; } ;
typedef  TYPE_1__ solaris_cpu_t ;
struct TYPE_6__ {scalar_t__ fbtp_roffset; scalar_t__ fbtp_rval; uintptr_t fbtp_savedval; scalar_t__ fbtp_patchpoint; int /*<<< orphan*/  fbtp_id; struct TYPE_6__* fbtp_hashnext; } ;
typedef  TYPE_2__ fbt_probe_t ;

/* Variables and functions */
 scalar_t__ DTRACE_INVOP_JUMP ; 
 size_t FBT_ADDR2NDX (uintptr_t) ; 
 uintptr_t FBT_BR_MASK ; 
 size_t curcpu ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 TYPE_2__** fbt_probetab ; 
 TYPE_1__* solaris_cpu ; 

int
fbt_invop(uintptr_t addr, struct trapframe *frame, uintptr_t rval)
{
	solaris_cpu_t *cpu = &solaris_cpu[curcpu];
	fbt_probe_t *fbt = fbt_probetab[FBT_ADDR2NDX(addr)];
	uintptr_t tmp;

	for (; fbt != NULL; fbt = fbt->fbtp_hashnext) {
		if ((uintptr_t)fbt->fbtp_patchpoint == addr) {
			if (fbt->fbtp_roffset == 0) {
				cpu->cpu_dtrace_caller = addr;

				dtrace_probe(fbt->fbtp_id, frame->fixreg[3],
				    frame->fixreg[4], frame->fixreg[5],
				    frame->fixreg[6], frame->fixreg[7]);

				cpu->cpu_dtrace_caller = 0;
			} else {

				dtrace_probe(fbt->fbtp_id, fbt->fbtp_roffset,
				    rval, 0, 0, 0);
				/*
				 * The caller doesn't have the fbt item, so
				 * fixup tail calls here.
				 */
				if (fbt->fbtp_rval == DTRACE_INVOP_JUMP) {
					frame->srr0 = (uintptr_t)fbt->fbtp_patchpoint;
					tmp = fbt->fbtp_savedval & FBT_BR_MASK;
					/* Sign extend. */
					if (tmp & 0x02000000)
#ifdef __powerpc64__
						tmp |= 0xfffffffffc000000ULL;
#else
						tmp |= 0xfc000000UL;
#endif
					frame->srr0 += tmp;
				}
				cpu->cpu_dtrace_caller = 0;
			}

			return (fbt->fbtp_rval);
		}
	}

	return (0);
}