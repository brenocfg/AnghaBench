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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  HPTEG_HASH_BITS_VPTE ; 
 int hash_64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 kvmppc_mmu_hash_vpte(u64 vpage)
{
	return hash_64(vpage & 0xfffffffffULL, HPTEG_HASH_BITS_VPTE);
}