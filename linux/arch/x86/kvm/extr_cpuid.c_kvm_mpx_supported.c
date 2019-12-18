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
struct TYPE_2__ {scalar_t__ (* mpx_supported ) () ;} ;

/* Variables and functions */
 int XFEATURE_MASK_BNDCSR ; 
 int XFEATURE_MASK_BNDREGS ; 
 int host_xcr0 ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ stub1 () ; 

bool kvm_mpx_supported(void)
{
	return ((host_xcr0 & (XFEATURE_MASK_BNDREGS | XFEATURE_MASK_BNDCSR))
		 && kvm_x86_ops->mpx_supported());
}