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
 int /*<<< orphan*/  HPTEG_HASH_BITS_PTE_LONG ; 
 int PTE_SIZE ; 
 int hash_64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 kvmppc_mmu_hash_pte_long(u64 eaddr)
{
	return hash_64((eaddr & 0x0ffff000) >> PTE_SIZE,
		       HPTEG_HASH_BITS_PTE_LONG);
}