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
struct trapframe {int tf_err; int tf_rflags; } ;

/* Variables and functions */
 int CPUID_STDEXT_SMAP ; 
 int PGEX_I ; 
 int PGEX_P ; 
 int PGEX_RSV ; 
 int PGEX_U ; 
 int PSL_AC ; 
 int cpu_stdext_feature ; 

__attribute__((used)) static bool
trap_is_smap(struct trapframe *frame)
{

	/*
	 * A page fault on a userspace address is classified as
	 * SMAP-induced if:
	 * - SMAP is supported;
	 * - kernel mode accessed present data page;
	 * - rflags.AC was cleared.
	 * Kernel must never access user space with rflags.AC cleared
	 * if SMAP is enabled.
	 */
	return ((cpu_stdext_feature & CPUID_STDEXT_SMAP) != 0 &&
	    (frame->tf_err & (PGEX_P | PGEX_U | PGEX_I | PGEX_RSV)) ==
	    PGEX_P && (frame->tf_rflags & PSL_AC) == 0);
}