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
typedef  scalar_t__ vm_paddr_t ;
typedef  int uintmax_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int RB_VERBOSE ; 
 int boothowto ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bufinit () ; 
 int /*<<< orphan*/  cpu_init_interrupts () ; 
 char* cpu_model ; 
 int /*<<< orphan*/  kmi ; 
 scalar_t__* phys_avail ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int ptoa (int) ; 
 scalar_t__ realmem ; 
 scalar_t__ vm_free_count () ; 
 int /*<<< orphan*/  vm_ksubmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_bufferinit () ; 

__attribute__((used)) static void
cpu_startup(void *dummy)
{

	if (boothowto & RB_VERBOSE)
		bootverbose++;

	printf("CPU model: %s\n", cpu_model);

	printf("real memory  = %ju (%juK bytes)\n", ptoa((uintmax_t)realmem),
	    ptoa((uintmax_t)realmem) / 1024);

	/*
	 * Display any holes after the first chunk of extended memory.
	 */
	if (bootverbose) {
		int indx;

		printf("Physical memory chunk(s):\n");
		for (indx = 0; phys_avail[indx + 1] != 0; indx += 2) {
			vm_paddr_t size1 = phys_avail[indx + 1] - phys_avail[indx];

			printf("0x%08jx - 0x%08jx, %ju bytes (%ju pages)\n",
			    (uintmax_t)phys_avail[indx],
			    (uintmax_t)phys_avail[indx + 1] - 1,
			    (uintmax_t)size1,
			    (uintmax_t)size1 / PAGE_SIZE);
		}
	}

	vm_ksubmap_init(&kmi);

	printf("avail memory = %ju (%juMB)\n", 
	    ptoa((uintmax_t)vm_free_count()),
	    ptoa((uintmax_t)vm_free_count()) / 1048576);
	cpu_init_interrupts();

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bufinit();
	vm_pager_bufferinit();
}