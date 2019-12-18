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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_mmio_spte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_dirty_mask ; 
 scalar_t__ spte_ad_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 spte_shadow_dirty_mask(u64 spte)
{
	MMU_WARN_ON(is_mmio_spte(spte));
	return spte_ad_enabled(spte) ? shadow_dirty_mask : 0;
}