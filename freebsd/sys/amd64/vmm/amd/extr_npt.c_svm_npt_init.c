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
 int NPT_IPIMASK ; 
 int PMAP_PDE_SUPERPAGE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int npt_flags ; 

int
svm_npt_init(int ipinum)
{
	int enable_superpage = 1;

	npt_flags = ipinum & NPT_IPIMASK;
	TUNABLE_INT_FETCH("hw.vmm.npt.enable_superpage", &enable_superpage);
	if (enable_superpage)
		npt_flags |= PMAP_PDE_SUPERPAGE; 
	
	return (0);
}