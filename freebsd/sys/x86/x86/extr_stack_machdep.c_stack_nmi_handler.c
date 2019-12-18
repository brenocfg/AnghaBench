#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct TYPE_3__ {scalar_t__ depth; } ;

/* Variables and functions */
 int PSL_I ; 
 int TF_FLAGS (struct trapframe*) ; 
 int /*<<< orphan*/  TF_FP (struct trapframe*) ; 
 int /*<<< orphan*/  TRAPF_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (long*,long) ; 
 scalar_t__ curthread ; 
 scalar_t__ nmi_pending ; 
 TYPE_1__* nmi_stack ; 
 int /*<<< orphan*/  stack_capture (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
stack_nmi_handler(struct trapframe *tf)
{

#ifdef STACK
	/* Don't consume an NMI that wasn't meant for us. */
	if (nmi_stack == NULL || curthread != nmi_pending)
		return (0);

	if (!TRAPF_USERMODE(tf) && (TF_FLAGS(tf) & PSL_I) != 0)
		stack_capture(curthread, nmi_stack, TF_FP(tf));
	else
		/* We were running in usermode or had interrupts disabled. */
		nmi_stack->depth = 0;

	atomic_store_rel_ptr((long *)&nmi_pending, (long)NULL);
	return (1);
#else
	return (0);
#endif
}