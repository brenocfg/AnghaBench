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
typedef  int vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct tdfx_softc {int addr0; int /*<<< orphan*/  memrange; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 int tdfx_count ; 
 int /*<<< orphan*/  tdfx_devclass ; 

__attribute__((used)) static int
tdfx_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	/* 
	 * mmap(2) is called by a user process to request that an area of memory
	 * associated with this device be mapped for the process to work with. Nprot
	 * holds the protections requested, PROT_READ, PROT_WRITE, or both.
	 */

	/**** OLD GET CONFIG ****/
	/* struct tdfx_softc* tdfx_info; */
	
	/* Get the configuration for our card XXX*/
	/*tdfx_info = dev->si_drv1; */
	/************************/

	struct tdfx_softc* tdfx_info[2];
	
	tdfx_info[0] = (struct tdfx_softc*)devclass_get_softc(tdfx_devclass, 0);

	/* If, for some reason, its not configured, we bail out */
	if(tdfx_info[0] == NULL) {
#ifdef	DEBUG
	   printf("tdfx: tdfx_info (softc) is NULL\n");
#endif
	   return -1;
	}

	/* We must stay within the bound of our address space */
	if((offset & 0xff000000) == tdfx_info[0]->addr0) {
		offset &= 0xffffff;
		*paddr = rman_get_start(tdfx_info[0]->memrange) + offset;
		return 0;
	}
	
	if(tdfx_count > 1) {
		tdfx_info[1] = (struct tdfx_softc*)devclass_get_softc(tdfx_devclass, 1);
		if((offset & 0xff000000) == tdfx_info[1]->addr0) {
			offset &= 0xffffff;
			*paddr = rman_get_start(tdfx_info[1]->memrange) +
			    offset;
			return 0;
		}
	}

	/* See if the Banshee/V3 LFB is being requested */
	/*if(tdfx_info->memrange2 != NULL && (offset & 0xff000000) ==
			tdfx_info->addr1) {
	  	offset &= 0xffffff;
		return atop(rman_get_start(tdfx_info[1]->memrange2) + offset);
	}*/ /* VoodooNG code */

	/* The ret call */
	/* atop -> address to page
	 * rman_get_start, get the (struct resource*)->r_start member,
	 * the mapping base address.
	 */
	return -1;
}