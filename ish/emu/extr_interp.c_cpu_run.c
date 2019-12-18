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
struct tlb {TYPE_1__* mem; } ;
struct cpu_state {int trapno; TYPE_1__* mem; } ;
struct TYPE_2__ {int changes; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int INT_NONE ; 
 int INT_TIMER ; 
 int cpu_step32 (struct cpu_state*,struct tlb*) ; 
 int /*<<< orphan*/  handle_interrupt (int) ; 
 int /*<<< orphan*/  read_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_wrunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_flush (struct tlb*) ; 

void cpu_run(struct cpu_state *cpu) {
    int i = 0;
    struct tlb tlb = {.mem = cpu->mem};
    tlb_flush(&tlb);
    read_wrlock(&cpu->mem->lock);
    int changes = cpu->mem->changes;
    while (true) {
        int interrupt = cpu_step32(cpu, &tlb);
        if (interrupt == INT_NONE && i++ >= 100000) {
            i = 0;
            interrupt = INT_TIMER;
        }
        if (interrupt != INT_NONE) {
            cpu->trapno = interrupt;
            read_wrunlock(&cpu->mem->lock);
            handle_interrupt(interrupt);
            read_wrlock(&cpu->mem->lock);
            if (tlb.mem != cpu->mem)
                tlb.mem = cpu->mem;
            if (cpu->mem->changes != changes) {
                tlb_flush(&tlb);
                changes = cpu->mem->changes;
            }
        }
    }
}