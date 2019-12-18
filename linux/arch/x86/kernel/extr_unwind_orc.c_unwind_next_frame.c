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
struct TYPE_2__ {int type; } ;
struct unwind_state {unsigned long ip; unsigned long sp; int signal; int error; unsigned long bp; int full_regs; TYPE_1__ stack_info; struct pt_regs* regs; int /*<<< orphan*/  graph_idx; int /*<<< orphan*/  task; } ;
struct pt_regs {unsigned long r10; unsigned long r13; unsigned long di; unsigned long dx; unsigned long bp; } ;
struct orc_entry {int sp_reg; unsigned long sp_offset; int type; int bp_reg; unsigned long bp_offset; int /*<<< orphan*/  end; } ;
typedef  enum stack_type { ____Placeholder_stack_type } stack_type ;

/* Variables and functions */
 int /*<<< orphan*/  IRET_FRAME_OFFSET ; 
#define  ORC_REG_BP 140 
#define  ORC_REG_BP_INDIRECT 139 
#define  ORC_REG_DI 138 
#define  ORC_REG_DX 137 
#define  ORC_REG_PREV_SP 136 
#define  ORC_REG_R10 135 
#define  ORC_REG_R13 134 
#define  ORC_REG_SP 133 
#define  ORC_REG_SP_INDIRECT 132 
#define  ORC_REG_UNDEFINED 131 
#define  ORC_TYPE_CALL 130 
#define  ORC_TYPE_REGS 129 
#define  ORC_TYPE_REGS_IRET 128 
 int STACK_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  deref_stack_iret_regs (struct unwind_state*,unsigned long,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  deref_stack_reg (struct unwind_state*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  deref_stack_regs (struct unwind_state*,unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long ftrace_graph_ret_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,void*) ; 
 scalar_t__ on_stack (TYPE_1__*,void*,int) ; 
 struct orc_entry* orc_find (int) ; 
 struct orc_entry orc_fp_entry ; 
 int /*<<< orphan*/  orc_warn (char*,void*,...) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ unwind_done (struct unwind_state*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

bool unwind_next_frame(struct unwind_state *state)
{
	unsigned long ip_p, sp, orig_ip = state->ip, prev_sp = state->sp;
	enum stack_type prev_type = state->stack_info.type;
	struct orc_entry *orc;
	bool indirect = false;

	if (unwind_done(state))
		return false;

	/* Don't let modules unload while we're reading their ORC data. */
	preempt_disable();

	/* End-of-stack check for user tasks: */
	if (state->regs && user_mode(state->regs))
		goto the_end;

	/*
	 * Find the orc_entry associated with the text address.
	 *
	 * Decrement call return addresses by one so they work for sibling
	 * calls and calls to noreturn functions.
	 */
	orc = orc_find(state->signal ? state->ip : state->ip - 1);
	if (!orc) {
		/*
		 * As a fallback, try to assume this code uses a frame pointer.
		 * This is useful for generated code, like BPF, which ORC
		 * doesn't know about.  This is just a guess, so the rest of
		 * the unwind is no longer considered reliable.
		 */
		orc = &orc_fp_entry;
		state->error = true;
	}

	/* End-of-stack check for kernel threads: */
	if (orc->sp_reg == ORC_REG_UNDEFINED) {
		if (!orc->end)
			goto err;

		goto the_end;
	}

	/* Find the previous frame's stack: */
	switch (orc->sp_reg) {
	case ORC_REG_SP:
		sp = state->sp + orc->sp_offset;
		break;

	case ORC_REG_BP:
		sp = state->bp + orc->sp_offset;
		break;

	case ORC_REG_SP_INDIRECT:
		sp = state->sp + orc->sp_offset;
		indirect = true;
		break;

	case ORC_REG_BP_INDIRECT:
		sp = state->bp + orc->sp_offset;
		indirect = true;
		break;

	case ORC_REG_R10:
		if (!state->regs || !state->full_regs) {
			orc_warn("missing regs for base reg R10 at ip %pB\n",
				 (void *)state->ip);
			goto err;
		}
		sp = state->regs->r10;
		break;

	case ORC_REG_R13:
		if (!state->regs || !state->full_regs) {
			orc_warn("missing regs for base reg R13 at ip %pB\n",
				 (void *)state->ip);
			goto err;
		}
		sp = state->regs->r13;
		break;

	case ORC_REG_DI:
		if (!state->regs || !state->full_regs) {
			orc_warn("missing regs for base reg DI at ip %pB\n",
				 (void *)state->ip);
			goto err;
		}
		sp = state->regs->di;
		break;

	case ORC_REG_DX:
		if (!state->regs || !state->full_regs) {
			orc_warn("missing regs for base reg DX at ip %pB\n",
				 (void *)state->ip);
			goto err;
		}
		sp = state->regs->dx;
		break;

	default:
		orc_warn("unknown SP base reg %d for ip %pB\n",
			 orc->sp_reg, (void *)state->ip);
		goto err;
	}

	if (indirect) {
		if (!deref_stack_reg(state, sp, &sp))
			goto err;
	}

	/* Find IP, SP and possibly regs: */
	switch (orc->type) {
	case ORC_TYPE_CALL:
		ip_p = sp - sizeof(long);

		if (!deref_stack_reg(state, ip_p, &state->ip))
			goto err;

		state->ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
						  state->ip, (void *)ip_p);

		state->sp = sp;
		state->regs = NULL;
		state->signal = false;
		break;

	case ORC_TYPE_REGS:
		if (!deref_stack_regs(state, sp, &state->ip, &state->sp)) {
			orc_warn("can't dereference registers at %p for ip %pB\n",
				 (void *)sp, (void *)orig_ip);
			goto err;
		}

		state->regs = (struct pt_regs *)sp;
		state->full_regs = true;
		state->signal = true;
		break;

	case ORC_TYPE_REGS_IRET:
		if (!deref_stack_iret_regs(state, sp, &state->ip, &state->sp)) {
			orc_warn("can't dereference iret registers at %p for ip %pB\n",
				 (void *)sp, (void *)orig_ip);
			goto err;
		}

		state->regs = (void *)sp - IRET_FRAME_OFFSET;
		state->full_regs = false;
		state->signal = true;
		break;

	default:
		orc_warn("unknown .orc_unwind entry type %d for ip %pB\n",
			 orc->type, (void *)orig_ip);
		break;
	}

	/* Find BP: */
	switch (orc->bp_reg) {
	case ORC_REG_UNDEFINED:
		if (state->regs && state->full_regs)
			state->bp = state->regs->bp;
		break;

	case ORC_REG_PREV_SP:
		if (!deref_stack_reg(state, sp + orc->bp_offset, &state->bp))
			goto err;
		break;

	case ORC_REG_BP:
		if (!deref_stack_reg(state, state->bp + orc->bp_offset, &state->bp))
			goto err;
		break;

	default:
		orc_warn("unknown BP base reg %d for ip %pB\n",
			 orc->bp_reg, (void *)orig_ip);
		goto err;
	}

	/* Prevent a recursive loop due to bad ORC data: */
	if (state->stack_info.type == prev_type &&
	    on_stack(&state->stack_info, (void *)state->sp, sizeof(long)) &&
	    state->sp <= prev_sp) {
		orc_warn("stack going in the wrong direction? ip=%pB\n",
			 (void *)orig_ip);
		goto err;
	}

	preempt_enable();
	return true;

err:
	state->error = true;

the_end:
	preempt_enable();
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	return false;
}