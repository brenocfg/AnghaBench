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
typedef  void* u32 ;
struct apm_bios_call {int err; void* eax; void* ecx; void* ebx; void* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  __apm_bios_call_simple ; 
 int on_cpu0 (int /*<<< orphan*/ ,struct apm_bios_call*) ; 

__attribute__((used)) static int apm_bios_call_simple(u32 func, u32 ebx_in, u32 ecx_in, u32 *eax,
				int *err)
{
	struct apm_bios_call call;
	int ret;

	call.func = func;
	call.ebx = ebx_in;
	call.ecx = ecx_in;

	ret = on_cpu0(__apm_bios_call_simple, &call);
	*eax = call.eax;
	*err = call.err;
	return ret;
}