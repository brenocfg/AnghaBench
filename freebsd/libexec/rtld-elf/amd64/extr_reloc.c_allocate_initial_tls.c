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
typedef  int /*<<< orphan*/  Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_SET_FSBASE ; 
 int CPUID_STDEXT_FSGSBASE ; 
 scalar_t__ P_OSREL_WRFSBASE ; 
 scalar_t__ RTLD_STATIC_TLS_EXTRA ; 
 scalar_t__ __getosreldate () ; 
 void* allocate_tls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int cpu_stdext_feature ; 
 int /*<<< orphan*/  sysarch (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ tls_last_offset ; 
 scalar_t__ tls_static_space ; 
 int /*<<< orphan*/  wrfsbase (uintptr_t) ; 

void
allocate_initial_tls(Obj_Entry *objs)
{
	void *addr;

	/*
	 * Fix the size of the static TLS block by using the maximum
	 * offset allocated so far and adding a bit for dynamic
	 * modules to use.
	 */
	tls_static_space = tls_last_offset + RTLD_STATIC_TLS_EXTRA;

	addr = allocate_tls(objs, 0, 3 * sizeof(Elf_Addr), sizeof(Elf_Addr));
	if (__getosreldate() >= P_OSREL_WRFSBASE &&
	    (cpu_stdext_feature & CPUID_STDEXT_FSGSBASE) != 0)
		wrfsbase((uintptr_t)addr);
	else
		sysarch(AMD64_SET_FSBASE, &addr);
}