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

/* Variables and functions */
 int /*<<< orphan*/  EXFLAG_NOALLOC ; 
 int /*<<< orphan*/  EXFLAG_NODUMP ; 
 int /*<<< orphan*/  Maxmem ; 
 int /*<<< orphan*/  PHYS_AVAIL_ENTRIES ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dump_avail ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * phys_avail ; 
 int /*<<< orphan*/  physmem ; 
 int /*<<< orphan*/  realmem ; 
 size_t regions_to_avail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arm_physmem_init_kernel_globals(void)
{
	size_t nextidx;

	regions_to_avail(dump_avail, EXFLAG_NODUMP, PHYS_AVAIL_ENTRIES, NULL,
	    NULL);
	nextidx = regions_to_avail(phys_avail, EXFLAG_NOALLOC,
	    PHYS_AVAIL_ENTRIES, &physmem, &realmem);
	if (nextidx == 0)
		panic("No memory entries in phys_avail");
	Maxmem = atop(phys_avail[nextidx - 1]);
}