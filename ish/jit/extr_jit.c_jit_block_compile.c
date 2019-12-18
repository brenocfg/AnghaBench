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
struct tlb {int dummy; } ;
struct jit_block {int /*<<< orphan*/  used; } ;
struct gen_state {int ip; struct jit_block* block; int /*<<< orphan*/  capacity; } ;
typedef  int addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gen_end (struct gen_state*) ; 
 int /*<<< orphan*/  gen_exit (struct gen_state*) ; 
 int /*<<< orphan*/  gen_start (int,struct gen_state*) ; 
 int /*<<< orphan*/  gen_step32 (struct gen_state*,struct tlb*) ; 

__attribute__((used)) static struct jit_block *jit_block_compile(addr_t ip, struct tlb *tlb) {
    struct gen_state state;
    TRACE("%d %08x --- compiling:\n", current->pid, ip);
    gen_start(ip, &state);
    while (true) {
        if (!gen_step32(&state, tlb))
            break;
        // no block should span more than 2 pages
        // guarantee this by limiting total block size to 1 page
        // guarantee that by stopping as soon as there's less space left than
        // the maximum length of an x86 instruction
        // TODO refuse to decode instructions longer than 15 bytes
        if (state.ip - ip >= PAGE_SIZE - 15) {
            gen_exit(&state);
            break;
        }
    }
    gen_end(&state);
    assert(state.ip - ip <= PAGE_SIZE);
    state.block->used = state.capacity;
    return state.block;
}