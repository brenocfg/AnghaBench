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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmxctx {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * vmxctx_regptr (struct vmxctx*,int) ; 

__attribute__((used)) static int
vmxctx_getreg(struct vmxctx *vmxctx, int reg, uint64_t *retval)
{
	register_t *regp;

	if ((regp = vmxctx_regptr(vmxctx, reg)) != NULL) {
		*retval = *regp;
		return (0);
	} else
		return (EINVAL);
}