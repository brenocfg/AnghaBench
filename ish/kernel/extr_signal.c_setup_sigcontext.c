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
struct sigcontext_ {scalar_t__ trapno; int oldmask; int /*<<< orphan*/  cr2; int /*<<< orphan*/  flags; int /*<<< orphan*/  ip; int /*<<< orphan*/  sp_at_signal; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  si; int /*<<< orphan*/  di; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; } ;
struct cpu_state {scalar_t__ trapno; int /*<<< orphan*/  segfault_addr; int /*<<< orphan*/  eflags; int /*<<< orphan*/  eip; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
struct TYPE_2__ {int blocked; } ;

/* Variables and functions */
 scalar_t__ INT_GPF ; 
 int /*<<< orphan*/  collapse_flags (struct cpu_state*) ; 
 TYPE_1__* current ; 

__attribute__((used)) static void setup_sigcontext(struct sigcontext_ *sc, struct cpu_state *cpu) {
    sc->ax = cpu->eax;
    sc->bx = cpu->ebx;
    sc->cx = cpu->ecx;
    sc->dx = cpu->edx;
    sc->di = cpu->edi;
    sc->si = cpu->esi;
    sc->bp = cpu->ebp;
    sc->sp = sc->sp_at_signal = cpu->esp;
    sc->ip = cpu->eip;
    collapse_flags(cpu);
    sc->flags = cpu->eflags;
    sc->trapno = cpu->trapno;
    if (cpu->trapno == INT_GPF)
        sc->cr2 = cpu->segfault_addr;
    // TODO more shit
    sc->oldmask = current->blocked & 0xffffffff;
}