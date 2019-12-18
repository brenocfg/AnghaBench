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
struct TYPE_2__ {int /*<<< orphan*/  cache_coherent_dma; } ;

/* Variables and functions */
 int RB_KDB ; 
 int /*<<< orphan*/  TRUE ; 
 int boothowto ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  init_param1 () ; 
 int /*<<< orphan*/  init_param2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_enter (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdb_init () ; 
 int /*<<< orphan*/  mips_cpu_init () ; 
 int /*<<< orphan*/  mips_proc0_init () ; 
 int /*<<< orphan*/  mutex_init () ; 
 int /*<<< orphan*/  physmem ; 
 int /*<<< orphan*/  pmap_bootstrap () ; 

__attribute__((used)) static void
mips_init(void)
{
	init_param1();
	init_param2(physmem);

	mips_cpu_init();
	cpuinfo.cache_coherent_dma = TRUE;
	pmap_bootstrap();
	mips_proc0_init();
	mutex_init();
#ifdef DDB
	kdb_init();
	if (boothowto & RB_KDB) {
		kdb_enter("Boot flags requested debugger", NULL);
	}
#endif
}