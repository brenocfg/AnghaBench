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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct i386_frame {scalar_t__ f_retaddr; struct i386_frame* f_frame; } ;
typedef  scalar_t__ register_t ;
typedef  scalar_t__ pc_t ;
struct TYPE_4__ {scalar_t__ td_kstack; int td_kstack_pages; } ;
struct TYPE_3__ {scalar_t__ cpu_dtrace_caller; } ;

/* Variables and functions */
 int /*<<< orphan*/  INKERNEL (scalar_t__) ; 
 int PAGE_SIZE ; 
 size_t curcpu ; 
 TYPE_2__* curthread ; 
 TYPE_1__* solaris_cpu ; 

void
dtrace_getpcstack(pc_t *pcstack, int pcstack_limit, int aframes,
    uint32_t *intrpc)
{
	int depth = 0;
	register_t ebp;
	struct i386_frame *frame;
	vm_offset_t callpc;
	pc_t caller = (pc_t) solaris_cpu[curcpu].cpu_dtrace_caller;

	if (intrpc != 0)
		pcstack[depth++] = (pc_t) intrpc;

	aframes++;

	__asm __volatile("movl %%ebp,%0" : "=r" (ebp));

	frame = (struct i386_frame *)ebp;
	while (depth < pcstack_limit) {
		if (!INKERNEL(frame))
			break;

		callpc = frame->f_retaddr;

		if (!INKERNEL(callpc))
			break;

		if (aframes > 0) {
			aframes--;
			if ((aframes == 0) && (caller != 0)) {
				pcstack[depth++] = caller;
			}
		}
		else {
			pcstack[depth++] = callpc;
		}

		if (frame->f_frame <= frame ||
		    (vm_offset_t)frame->f_frame >= curthread->td_kstack +
		    curthread->td_kstack_pages * PAGE_SIZE)
			break;
		frame = frame->f_frame;
	}

	for (; depth < pcstack_limit; depth++) {
		pcstack[depth] = 0;
	}
}