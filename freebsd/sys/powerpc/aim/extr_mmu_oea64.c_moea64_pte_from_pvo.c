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
struct TYPE_2__ {int prot; int /*<<< orphan*/  pa; } ;
struct pvo_entry {int pvo_vpn; int pvo_vaddr; TYPE_1__ pvo_pte; } ;
struct lpte {int pte_hi; int /*<<< orphan*/  pte_lo; } ;

/* Variables and functions */
 int ADDR_API_SHFT64 ; 
 int ADDR_PIDX_SHFT ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_BIG ; 
 int /*<<< orphan*/  LPTE_BR ; 
 int /*<<< orphan*/  LPTE_BW ; 
 int LPTE_HID ; 
 int /*<<< orphan*/  LPTE_NOEXEC ; 
 int LPTE_VALID ; 
 int LPTE_WIRED ; 
 int PVO_HID ; 
 int PVO_LARGE ; 
 int PVO_WIRED ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 

void
moea64_pte_from_pvo(const struct pvo_entry *pvo, struct lpte *lpte)
{

	lpte->pte_hi = (pvo->pvo_vpn >> (ADDR_API_SHFT64 - ADDR_PIDX_SHFT)) &
	    LPTE_AVPN_MASK;
	lpte->pte_hi |= LPTE_VALID;
	
	if (pvo->pvo_vaddr & PVO_LARGE)
		lpte->pte_hi |= LPTE_BIG;
	if (pvo->pvo_vaddr & PVO_WIRED)
		lpte->pte_hi |= LPTE_WIRED;
	if (pvo->pvo_vaddr & PVO_HID)
		lpte->pte_hi |= LPTE_HID;

	lpte->pte_lo = pvo->pvo_pte.pa; /* Includes WIMG bits */
	if (pvo->pvo_pte.prot & VM_PROT_WRITE)
		lpte->pte_lo |= LPTE_BW;
	else
		lpte->pte_lo |= LPTE_BR;

	if (!(pvo->pvo_pte.prot & VM_PROT_EXECUTE))
		lpte->pte_lo |= LPTE_NOEXEC;
}