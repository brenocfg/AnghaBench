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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_EA_IMPREC ; 
 int /*<<< orphan*/  abort_fatal (struct trapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  userret (int /*<<< orphan*/ ,struct trapframe*) ; 

__attribute__((used)) static __inline void
abort_imprecise(struct trapframe *tf, u_int fsr, u_int prefetch, bool usermode)
{

	/*
	 * XXX - We can got imprecise abort as result of access
	 * to not-present PCI/PCIe configuration space.
	 */
#if 0
	goto out;
#endif
	abort_fatal(tf, FAULT_EA_IMPREC, fsr, 0, prefetch, curthread, NULL);

	/*
	 * Returning from this function means that we ignore
	 * the abort for good reason. Note that imprecise abort
	 * could fire any time even in user mode.
	 */

#if 0
out:
	if (usermode)
		userret(curthread, tf);
#endif
}