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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct reg {scalar_t__ r_rsp; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; } ;
struct TYPE_2__ {scalar_t__ p_model; } ;

/* Variables and functions */
 int CPU_DTRACE_BADADDR ; 
 int CPU_DTRACE_NOFAULT ; 
 scalar_t__ DATAMODEL_LP64 ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  dtrace_fulword (uintptr_t*) ; 
 int /*<<< orphan*/  dtrace_fuword32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
fasttrap_anarg(struct reg *rp, int function_entry, int argno)
{
	uint64_t value = 0;
	int shift = function_entry ? 1 : 0;

#ifdef __amd64
	if (curproc->p_model == DATAMODEL_LP64) {
		uintptr_t *stack;

		/*
		 * In 64-bit mode, the first six arguments are stored in
		 * registers.
		 */
		if (argno < 6)
			switch (argno) {
			case 0:
				return (rp->r_rdi);
			case 1:
				return (rp->r_rsi);
			case 2:
				return (rp->r_rdx);
			case 3:
				return (rp->r_rcx);
			case 4:
				return (rp->r_r8);
			case 5:
				return (rp->r_r9);
			}

		stack = (uintptr_t *)rp->r_rsp;
		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
		value = dtrace_fulword(&stack[argno - 6 + shift]);
		DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT | CPU_DTRACE_BADADDR);
	} else {
#endif
		uint32_t *stack = (uint32_t *)rp->r_rsp;
		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
		value = dtrace_fuword32(&stack[argno + shift]);
		DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT | CPU_DTRACE_BADADDR);
#ifdef __amd64
	}
#endif

	return (value);
}