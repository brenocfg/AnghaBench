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
struct unwind_state {int /*<<< orphan*/ * registers; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sf_pc; int /*<<< orphan*/  sf_lr; int /*<<< orphan*/  sf_sp; int /*<<< orphan*/  sf_r11; } ;
struct pcb {TYPE_1__ pcb_regs; } ;

/* Variables and functions */
 size_t FP ; 
 size_t LR ; 
 size_t PC ; 
 size_t SP ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  db_stack_trace_cmd (struct unwind_state*) ; 
 int /*<<< orphan*/  db_trace_self () ; 
 struct pcb* kdb_thr_ctx (struct thread*) ; 

int
db_trace_thread(struct thread *thr, int count)
{
	struct unwind_state state;
	struct pcb *ctx;

	if (thr != curthread) {
		ctx = kdb_thr_ctx(thr);

		state.registers[FP] = ctx->pcb_regs.sf_r11;
		state.registers[SP] = ctx->pcb_regs.sf_sp;
		state.registers[LR] = ctx->pcb_regs.sf_lr;
		state.registers[PC] = ctx->pcb_regs.sf_pc;

		db_stack_trace_cmd(&state);
	} else
		db_trace_self();
	return (0);
}