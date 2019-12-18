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
typedef  int vm_offset_t ;
typedef  int u_int ;
struct pte {int pte_hi; } ;

/* Variables and functions */
 int ADDR_API_SHFT ; 
 int PTE_API ; 
 int PTE_VALID ; 
 int PTE_VSID_SHFT ; 
 int SR_VSID_MASK ; 

__attribute__((used)) static __inline int
moea_pte_match(struct pte *pt, u_int sr, vm_offset_t va, int which)
{
	return (pt->pte_hi & ~PTE_VALID) ==
	    (((sr & SR_VSID_MASK) << PTE_VSID_SHFT) |
	    ((va >> ADDR_API_SHFT) & PTE_API) | which);
}