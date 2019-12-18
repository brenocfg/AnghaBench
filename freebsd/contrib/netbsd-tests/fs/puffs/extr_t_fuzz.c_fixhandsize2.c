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
struct puffs_kargs {int pa_fhflags; int pa_fhsize; } ;

/* Variables and functions */
 int PUFFS_FHFLAG_NFSV2 ; 
 int PUFFS_FHFLAG_NFSV3 ; 

__attribute__((used)) static void
fixhandsize2(struct puffs_kargs *kargs)
{

	/* XXX: values */
	if (kargs->pa_fhflags & PUFFS_FHFLAG_NFSV3)
		kargs->pa_fhsize %= 60;
	if (kargs->pa_fhflags & PUFFS_FHFLAG_NFSV2)
		kargs->pa_fhsize %= 28;
}