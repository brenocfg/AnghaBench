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
typedef  int vm_paddr_t ;
struct TYPE_2__ {scalar_t__ mr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long PAGE_SIZE ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bufinit () ; 
 int /*<<< orphan*/  clock ; 
 int /*<<< orphan*/  cpu_identify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  kmi ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rdpr (int /*<<< orphan*/ ) ; 
 long realmem ; 
 int /*<<< orphan*/  shutdown_final ; 
 TYPE_1__* sparc64_memreg ; 
 char* sparc64_model ; 
 int sparc64_nmemreg ; 
 int /*<<< orphan*/  sparc64_shutdown_final ; 
 int /*<<< orphan*/  ver ; 
 int vm_free_count () ; 
 int /*<<< orphan*/  vm_ksubmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_bufferinit () ; 

__attribute__((used)) static void
cpu_startup(void *arg)
{
	vm_paddr_t physsz;
	int i;

	physsz = 0;
	for (i = 0; i < sparc64_nmemreg; i++)
		physsz += sparc64_memreg[i].mr_size;
	printf("real memory  = %lu (%lu MB)\n", physsz,
	    physsz / (1024 * 1024));
	realmem = (long)physsz / PAGE_SIZE;

	vm_ksubmap_init(&kmi);

	bufinit();
	vm_pager_bufferinit();

	EVENTHANDLER_REGISTER(shutdown_final, sparc64_shutdown_final, NULL,
	    SHUTDOWN_PRI_LAST);

	printf("avail memory = %lu (%lu MB)\n", vm_free_count() * PAGE_SIZE,
	    vm_free_count() / ((1024 * 1024) / PAGE_SIZE));

	if (bootverbose)
		printf("machine: %s\n", sparc64_model);

	cpu_identify(rdpr(ver), PCPU_GET(clock), curcpu);
}