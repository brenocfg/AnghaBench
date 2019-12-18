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
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int uint_t ;
struct trapframe {int /*<<< orphan*/  exc; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  cr; int /*<<< orphan*/  lr; int /*<<< orphan*/ * fixreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 

ulong_t
dtrace_getreg(struct trapframe *rp, uint_t reg)
{
	if (reg < 32)
		return (rp->fixreg[reg]);

	switch (reg) {
	case 32:
		return (rp->lr);
	case 33:
		return (rp->cr);
	case 34:
		return (rp->xer);
	case 35:
		return (rp->ctr);
	case 36:
		return (rp->srr0);
	case 37:
		return (rp->srr1);
	case 38:
		return (rp->exc);
	default:
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}
}