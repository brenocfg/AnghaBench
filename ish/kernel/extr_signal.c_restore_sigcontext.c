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
struct sigcontext_ {int flags; int /*<<< orphan*/  ip; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  si; int /*<<< orphan*/  di; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; } ;
struct cpu_state {int eflags; int /*<<< orphan*/  eip; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 int USE_FLAGS ; 
 int /*<<< orphan*/  collapse_flags (struct cpu_state*) ; 

__attribute__((used)) static void restore_sigcontext(struct sigcontext_ *context, struct cpu_state *cpu) {
    cpu->eax = context->ax;
    cpu->ebx = context->bx;
    cpu->ecx = context->cx;
    cpu->edx = context->dx;
    cpu->edi = context->di;
    cpu->esi = context->si;
    cpu->ebp = context->bp;
    cpu->esp = context->sp;
    cpu->eip = context->ip;
    collapse_flags(cpu);

    // Use AC, RF, OF, DF, TF, SF, ZF, AF, PF, CF
#define USE_FLAGS 0b1010000110111010101
    cpu->eflags = (context->flags & USE_FLAGS) | (cpu->eflags & ~USE_FLAGS);
}