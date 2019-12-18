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
typedef  int vm_offset_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int slot; } ;
struct pvo_entry {int pvo_vaddr; int pvo_vpn; TYPE_1__ pvo_pte; int /*<<< orphan*/  pvo_pmap; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ADDR_PIDX ; 
 int ADDR_PIDX_SHFT ; 
 int ADDR_POFF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PVO_LARGE ; 
 int VSID_HASH_MASK ; 
 int moea64_large_page_shift ; 
 int moea64_pteg_mask ; 
 int va_to_vsid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_pvo_entry(struct pvo_entry *pvo, pmap_t pmap, vm_offset_t va)
{
	uint64_t vsid;
	uint64_t hash;
	int shift;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	pvo->pvo_pmap = pmap;
	va &= ~ADDR_POFF;
	pvo->pvo_vaddr |= va;
	vsid = va_to_vsid(pmap, va);
	pvo->pvo_vpn = (uint64_t)((va & ADDR_PIDX) >> ADDR_PIDX_SHFT)
	    | (vsid << 16);

	shift = (pvo->pvo_vaddr & PVO_LARGE) ? moea64_large_page_shift :
	    ADDR_PIDX_SHFT;
	hash = (vsid & VSID_HASH_MASK) ^ (((uint64_t)va & ADDR_PIDX) >> shift);
	pvo->pvo_pte.slot = (hash & moea64_pteg_mask) << 3;
}