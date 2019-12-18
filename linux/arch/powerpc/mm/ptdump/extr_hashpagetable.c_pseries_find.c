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
typedef  int u64 ;
struct hash_pte {int v; int r; } ;
struct TYPE_2__ {unsigned long shift; } ;

/* Variables and functions */
 unsigned long HPTES_PER_GROUP ; 
 scalar_t__ HPTE_V_COMPARE (int,unsigned long) ; 
 int HPTE_V_VALID ; 
 long H_SUCCESS ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_hash (unsigned long,unsigned long,int) ; 
 unsigned long hpt_vpn (unsigned long,unsigned long,int) ; 
 unsigned long hpte_encode_avpn (unsigned long,int,int) ; 
 unsigned long htab_hash_mask ; 
 int mmu_kernel_ssize ; 
 TYPE_1__* mmu_psize_defs ; 
 long plpar_pte_read_4 (int /*<<< orphan*/ ,unsigned long,void*) ; 

__attribute__((used)) static int pseries_find(unsigned long ea, int psize, bool primary, u64 *v, u64 *r)
{
	struct hash_pte ptes[4];
	unsigned long vsid, vpn, hash, hpte_group, want_v;
	int i, j, ssize = mmu_kernel_ssize;
	long lpar_rc = 0;
	unsigned long shift = mmu_psize_defs[psize].shift;

	/* calculate hash */
	vsid = get_kernel_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shift, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondary hash table, we invert the hash */
	if (!primary)
		hash = ~hash;
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	/* see if we can find an entry in the hpte with this hash */
	for (i = 0; i < HPTES_PER_GROUP; i += 4, hpte_group += 4) {
		lpar_rc = plpar_pte_read_4(0, hpte_group, (void *)ptes);

		if (lpar_rc != H_SUCCESS)
			continue;
		for (j = 0; j < 4; j++) {
			if (HPTE_V_COMPARE(ptes[j].v, want_v) &&
					(ptes[j].v & HPTE_V_VALID)) {
				/* HPTE matches */
				*v = ptes[j].v;
				*r = ptes[j].r;
				return 0;
			}
		}
	}
	return -1;
}