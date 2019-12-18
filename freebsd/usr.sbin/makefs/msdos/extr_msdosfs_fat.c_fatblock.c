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
typedef  int u_long ;
struct msdosfsmount {int pm_fatblocksize; int pm_fatblocksec; int pm_FATsecs; int pm_curfat; scalar_t__ pm_fatblk; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int MIN (int,int) ; 

__attribute__((used)) static void
fatblock(struct msdosfsmount *pmp, u_long ofs, u_long *bnp, u_long *sizep,
    u_long *bop)
{
	u_long bn, size;

	bn = ofs / pmp->pm_fatblocksize * pmp->pm_fatblocksec;
	size = MIN(pmp->pm_fatblocksec, pmp->pm_FATsecs - bn)
	    * DEV_BSIZE;
	bn += pmp->pm_fatblk + pmp->pm_curfat * pmp->pm_FATsecs;

	if (bnp)
		*bnp = bn;
	if (sizep)
		*sizep = size;
	if (bop)
		*bop = ofs % pmp->pm_fatblocksize;
}