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
struct TYPE_2__ {scalar_t__ bi_envp; } ;

/* Variables and functions */
 int CPUID_PAE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 TYPE_1__ bootinfo ; 
 int cpu_feature ; 
 int /*<<< orphan*/  init_static_kenv (char*,int /*<<< orphan*/ ) ; 
 int pae_mode ; 
 int /*<<< orphan*/ * pmap_methods_ptr ; 
 int /*<<< orphan*/  pmap_nopae_cold () ; 
 int /*<<< orphan*/  pmap_nopae_methods ; 
 int /*<<< orphan*/  pmap_pae_cold () ; 
 int /*<<< orphan*/  pmap_pae_methods ; 

void
pmap_cold(void)
{

	init_static_kenv((char *)bootinfo.bi_envp, 0);
	pae_mode = (cpu_feature & CPUID_PAE) != 0;
	if (pae_mode)
		TUNABLE_INT_FETCH("vm.pmap.pae_mode", &pae_mode);
	if (pae_mode) {
		pmap_methods_ptr = &pmap_pae_methods;
		pmap_pae_cold();
	} else {
		pmap_methods_ptr = &pmap_nopae_methods;
		pmap_nopae_cold();
	}
}