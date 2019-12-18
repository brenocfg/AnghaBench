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
typedef  int /*<<< orphan*/  uc_engine ;
struct tlb {int dummy; } ;
struct cpu_state {int /*<<< orphan*/  mem; } ;
struct TYPE_4__ {struct cpu_state cpu; TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 scalar_t__ compare_cpus (struct cpu_state*,struct tlb*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_step32 (struct cpu_state*,struct tlb*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  debugger ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/ * start_unicorn (struct cpu_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  step_tracing (struct cpu_state*,struct tlb*,int /*<<< orphan*/ *) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  tlb_init (struct tlb*,int /*<<< orphan*/ ) ; 
 int undefined_flags_mask (struct cpu_state*,struct tlb*) ; 
 int xX_main_Xx (int,char* const*,int /*<<< orphan*/ *) ; 

int main(int argc, char *const argv[]) {
    int err = xX_main_Xx(argc, argv, NULL);
    if (err < 0) {
        // FIXME this often prints the wrong error message on non-x86_64
        fprintf(stderr, "%s\n", strerror(-err));
        return err;
    }

    // create a unicorn and set it up exactly the same as the current process
    uc_engine *uc = start_unicorn(&current->cpu, &current->mm->mem);

    struct cpu_state *cpu = &current->cpu;
    struct tlb tlb;
    tlb_init(&tlb, cpu->mem);
    int undefined_flags = 0;
    struct cpu_state old_cpu = *cpu;
    while (true) {
        while (compare_cpus(cpu, &tlb, uc, undefined_flags) < 0) {
            printk("resetting cpu\n");
            *cpu = old_cpu;
            debugger;
            cpu_step32(cpu, &tlb);
        }
        undefined_flags = undefined_flags_mask(cpu, &tlb);
        old_cpu = *cpu;
        step_tracing(cpu, &tlb, uc);
    }
}