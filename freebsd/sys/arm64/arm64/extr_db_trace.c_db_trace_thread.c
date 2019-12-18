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
typedef  void* uint64_t ;
struct unwind_state {void* pc; void* fp; void* sp; } ;
struct thread {int dummy; } ;
struct pcb {scalar_t__* pcb_x; scalar_t__ pcb_sp; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  db_stack_trace_cmd (struct unwind_state*) ; 
 int /*<<< orphan*/  db_trace_self () ; 
 struct pcb* kdb_thr_ctx (struct thread*) ; 

int
db_trace_thread(struct thread *thr, int count)
{
	struct unwind_state frame;
	struct pcb *ctx;

	if (thr != curthread) {
		ctx = kdb_thr_ctx(thr);

		frame.sp = (uint64_t)ctx->pcb_sp;
		frame.fp = (uint64_t)ctx->pcb_x[29];
		frame.pc = (uint64_t)ctx->pcb_x[30];
		db_stack_trace_cmd(&frame);
	} else
		db_trace_self();
	return (0);
}