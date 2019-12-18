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
struct tlb {int dummy; } ;
struct cpu_state {int /*<<< orphan*/  eip; } ;
struct jit_frame {struct cpu_state cpu; } ;
struct jit_block {int dummy; } ;
struct gen_state {struct jit_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_end (struct gen_state*) ; 
 int /*<<< orphan*/  gen_exit (struct gen_state*) ; 
 int /*<<< orphan*/  gen_start (int /*<<< orphan*/ ,struct gen_state*) ; 
 int /*<<< orphan*/  gen_step32 (struct gen_state*,struct tlb*) ; 
 int /*<<< orphan*/  jit_block_free (int /*<<< orphan*/ *,struct jit_block*) ; 
 int jit_enter (struct jit_block*,struct jit_frame*,struct tlb*) ; 

int cpu_step32(struct cpu_state *cpu, struct tlb *tlb) {
    struct gen_state state;
    gen_start(cpu->eip, &state);
    gen_step32(&state, tlb);
    gen_exit(&state);
    gen_end(&state);

    struct jit_block *block = state.block;
    struct jit_frame frame = {.cpu = *cpu};
    int interrupt = jit_enter(block, &frame, tlb);
    *cpu = frame.cpu;
    jit_block_free(NULL, block);
    return interrupt;
}