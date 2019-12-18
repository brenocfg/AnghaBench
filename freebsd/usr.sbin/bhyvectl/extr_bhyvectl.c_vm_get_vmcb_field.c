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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_ACCESS (int,int) ; 
 int vm_get_register (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vm_get_vmcb_field(struct vmctx *ctx, int vcpu, int off, int bytes,
	uint64_t *ret_val)
{

	return (vm_get_register(ctx, vcpu, VMCB_ACCESS(off, bytes), ret_val));
}