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
struct vmx {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CTR1 (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vmx_astpending_trace(struct vmx *vmx, int vcpu, uint64_t rip)
{
#ifdef KTR
	VCPU_CTR1(vmx->vm, vcpu, "astpending vmexit at 0x%0lx", rip);
#endif
}