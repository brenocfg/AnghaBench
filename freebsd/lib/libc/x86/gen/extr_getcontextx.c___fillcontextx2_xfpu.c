#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* addr; void* len; } ;
typedef  TYPE_2__ x86_get_xfpustate_t ;
struct TYPE_5__ {int /*<<< orphan*/  mc_flags; void* mc_xfpustate_len; scalar_t__ mc_xfpustate; } ;
struct TYPE_7__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_3__ ucontext_t ;
typedef  scalar_t__ __register_t ;

/* Variables and functions */
 int /*<<< orphan*/  X86_GET_XFPUSTATE ; 
 int /*<<< orphan*/  _MC_HASFPXSTATE ; 
 int sysarch (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* xstate_sz ; 

__attribute__((used)) static int
__fillcontextx2_xfpu(char *ctx)
{
	x86_get_xfpustate_t xfpu;
	ucontext_t *ucp;

	ucp = (ucontext_t *)ctx;
	xfpu.addr = (char *)(ucp + 1);
	xfpu.len = xstate_sz;
	if (sysarch(X86_GET_XFPUSTATE, &xfpu) == -1)
		return (-1);
	ucp->uc_mcontext.mc_xfpustate = (__register_t)xfpu.addr;
	ucp->uc_mcontext.mc_xfpustate_len = xstate_sz;
	ucp->uc_mcontext.mc_flags |= _MC_HASFPXSTATE;
	return (0);
}