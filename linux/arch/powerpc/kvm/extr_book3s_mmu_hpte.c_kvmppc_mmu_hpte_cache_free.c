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
struct hpte_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpte_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct hpte_cache*) ; 

void kvmppc_mmu_hpte_cache_free(struct hpte_cache *pte)
{
	kmem_cache_free(hpte_cache, pte);
}