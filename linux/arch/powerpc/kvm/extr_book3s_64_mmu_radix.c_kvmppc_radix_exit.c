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

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pmd_cache ; 
 int /*<<< orphan*/  kvm_pte_cache ; 

void kvmppc_radix_exit(void)
{
	kmem_cache_destroy(kvm_pte_cache);
	kmem_cache_destroy(kvm_pmd_cache);
}