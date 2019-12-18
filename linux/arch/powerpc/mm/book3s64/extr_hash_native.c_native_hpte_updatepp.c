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
struct hash_pte {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOW (char*,...) ; 
 unsigned long HPTE_LOCAL_UPDATE ; 
 unsigned long HPTE_NOHPTE_UPDATE ; 
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_N ; 
 unsigned long HPTE_R_PPP ; 
 unsigned long HPTE_V_AVPN ; 
 int /*<<< orphan*/  HPTE_V_COMPARE (unsigned long,unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 unsigned long hpte_encode_avpn (unsigned long,int,int) ; 
 unsigned long hpte_get_old_v (struct hash_pte*) ; 
 struct hash_pte* htab_address ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long native_hpte_updatepp(unsigned long slot, unsigned long newpp,
				 unsigned long vpn, int bpsize,
				 int apsize, int ssize, unsigned long flags)
{
	struct hash_pte *hptep = htab_address + slot;
	unsigned long hpte_v, want_v;
	int ret = 0, local = 0;

	want_v = hpte_encode_avpn(vpn, bpsize, ssize);

	DBG_LOW("    update(vpn=%016lx, avpnv=%016lx, group=%lx, newpp=%lx)",
		vpn, want_v & HPTE_V_AVPN, slot, newpp);

	hpte_v = hpte_get_old_v(hptep);
	/*
	 * We need to invalidate the TLB always because hpte_remove doesn't do
	 * a tlb invalidate. If a hash bucket gets full, we "evict" a more/less
	 * random entry from it. When we do that we don't invalidate the TLB
	 * (hpte_remove) because we assume the old translation is still
	 * technically "valid".
	 */
	if (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID)) {
		DBG_LOW(" -> miss\n");
		ret = -1;
	} else {
		native_lock_hpte(hptep);
		/* recheck with locks held */
		hpte_v = hpte_get_old_v(hptep);
		if (unlikely(!HPTE_V_COMPARE(hpte_v, want_v) ||
			     !(hpte_v & HPTE_V_VALID))) {
			ret = -1;
		} else {
			DBG_LOW(" -> hit\n");
			/* Update the HPTE */
			hptep->r = cpu_to_be64((be64_to_cpu(hptep->r) &
						~(HPTE_R_PPP | HPTE_R_N)) |
					       (newpp & (HPTE_R_PPP | HPTE_R_N |
							 HPTE_R_C)));
		}
		native_unlock_hpte(hptep);
	}

	if (flags & HPTE_LOCAL_UPDATE)
		local = 1;
	/*
	 * Ensure it is out of the tlb too if it is not a nohpte fault
	 */
	if (!(flags & HPTE_NOHPTE_UPDATE))
		tlbie(vpn, bpsize, apsize, ssize, local);

	return ret;
}