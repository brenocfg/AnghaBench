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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ EALREADY ; 
 int PM1_ALWAYS_ZERO ; 
 int PM1_SCI_EN ; 
 int PM1_SLP_EN ; 
 int PM1_SLP_TYP ; 
 int /*<<< orphan*/  VM_SUSPEND_POWEROFF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int pm1_control ; 
 int vm_suspend (struct vmctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pm1_control_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
    uint32_t *eax, void *arg)
{
	int error;

	if (bytes != 2)
		return (-1);
	if (in)
		*eax = pm1_control;
	else {
		/*
		 * Various bits are write-only or reserved, so force them
		 * to zero in pm1_control.  Always preserve SCI_EN as OSPM
		 * can never change it.
		 */
		pm1_control = (pm1_control & PM1_SCI_EN) |
		    (*eax & ~(PM1_SLP_EN | PM1_ALWAYS_ZERO));

		/*
		 * If SLP_EN is set, check for S5.  Bhyve's _S5_ method
		 * says that '5' should be stored in SLP_TYP for S5.
		 */
		if (*eax & PM1_SLP_EN) {
			if ((pm1_control & PM1_SLP_TYP) >> 10 == 5) {
				error = vm_suspend(ctx, VM_SUSPEND_POWEROFF);
				assert(error == 0 || errno == EALREADY);
			}
		}
	}
	return (0);
}