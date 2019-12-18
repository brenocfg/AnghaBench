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
struct proc {int p_flag2; int p_fctl0; } ;

/* Variables and functions */
 int NT_FREEBSD_FCTL_PROTMAX_DISABLE ; 
 int P2_PROTMAX_DISABLE ; 
 int P2_PROTMAX_ENABLE ; 
 int PROT_NONE ; 
 int _PROT_ALL ; 
 scalar_t__ imply_prot_max ; 

int
kern_mmap_maxprot(struct proc *p, int prot)
{

	if ((p->p_flag2 & P2_PROTMAX_DISABLE) != 0 ||
	    (p->p_fctl0 & NT_FREEBSD_FCTL_PROTMAX_DISABLE) != 0)
		return (_PROT_ALL);
	if (((p->p_flag2 & P2_PROTMAX_ENABLE) != 0 || imply_prot_max) &&
	    prot != PROT_NONE)
		 return (prot);
	return (_PROT_ALL);
}