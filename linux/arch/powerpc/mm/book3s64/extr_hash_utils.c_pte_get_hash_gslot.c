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
typedef  int /*<<< orphan*/  real_pte_t ;

/* Variables and functions */
 unsigned long HPTES_PER_GROUP ; 
 unsigned long _PTEIDX_GROUP_IX ; 
 unsigned long _PTEIDX_SECONDARY ; 
 unsigned long __rpte_to_hidx (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long hpt_hash (unsigned long,unsigned long,int) ; 
 unsigned long htab_hash_mask ; 

unsigned long pte_get_hash_gslot(unsigned long vpn, unsigned long shift,
		int ssize, real_pte_t rpte, unsigned int subpg_index)
{
	unsigned long hash, gslot, hidx;

	hash = hpt_hash(vpn, shift, ssize);
	hidx = __rpte_to_hidx(rpte, subpg_index);
	if (hidx & _PTEIDX_SECONDARY)
		hash = ~hash;
	gslot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	gslot += hidx & _PTEIDX_GROUP_IX;
	return gslot;
}