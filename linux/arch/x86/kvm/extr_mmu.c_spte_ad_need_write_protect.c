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
 int /*<<< orphan*/  MMU_WARN_ON (int /*<<< orphan*/ ) ; 
 int SPTE_AD_ENABLED_MASK ; 
 int SPTE_SPECIAL_MASK ; 
 int /*<<< orphan*/  is_mmio_spte (int) ; 

__attribute__((used)) static inline bool spte_ad_need_write_protect(u64 spte)
{
	MMU_WARN_ON(is_mmio_spte(spte));
	return (spte & SPTE_SPECIAL_MASK) != SPTE_AD_ENABLED_MASK;
}