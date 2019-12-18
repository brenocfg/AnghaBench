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
typedef  size_t u_long ;
struct msdosfsmount {size_t pm_maxcluster; int pm_flags; unsigned int* pm_inusemap; scalar_t__ pm_freeclustercount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MSDOSFSMNT_RONLY ; 
 int /*<<< orphan*/  MSDOSFS_ASSERT_MP_LOCKED (struct msdosfsmount*) ; 
 int MSDOSFS_FSIMOD ; 
 size_t N_INUSEBITS ; 

__attribute__((used)) static __inline void
usemap_alloc(struct msdosfsmount *pmp, u_long cn)
{

	MSDOSFS_ASSERT_MP_LOCKED(pmp);

	KASSERT(cn <= pmp->pm_maxcluster, ("cn too large %lu %lu", cn,
	    pmp->pm_maxcluster));
	KASSERT((pmp->pm_flags & MSDOSFSMNT_RONLY) == 0,
	    ("usemap_alloc on ro msdosfs mount"));
	KASSERT((pmp->pm_inusemap[cn / N_INUSEBITS] &
	    (1U << (cn % N_INUSEBITS))) == 0,
	    ("Allocating used sector %ld %ld %x", cn, cn % N_INUSEBITS,
	    (unsigned)pmp->pm_inusemap[cn / N_INUSEBITS]));
	pmp->pm_inusemap[cn / N_INUSEBITS] |= 1U << (cn % N_INUSEBITS);
	KASSERT(pmp->pm_freeclustercount > 0, ("usemap_alloc: too little"));
	pmp->pm_freeclustercount--;
	pmp->pm_flags |= MSDOSFS_FSIMOD;
}