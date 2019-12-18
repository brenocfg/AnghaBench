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
struct vcpu_vmx {int secondary_exec_control; } ;

/* Variables and functions */
 int SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE ; 

__attribute__((used)) static inline bool vmx_has_waitpkg(struct vcpu_vmx *vmx)
{
	return vmx->secondary_exec_control &
		SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE;
}