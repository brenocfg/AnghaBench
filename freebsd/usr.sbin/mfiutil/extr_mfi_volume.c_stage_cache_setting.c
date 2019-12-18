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
typedef  int /*<<< orphan*/  uint8_t ;
struct mfi_ld_props {int /*<<< orphan*/  default_cache_policy; } ;

/* Variables and functions */

__attribute__((used)) static void
stage_cache_setting(struct mfi_ld_props *props, uint8_t new_policy,
    uint8_t mask)
{

	props->default_cache_policy &= ~mask;
	props->default_cache_policy |= new_policy;
}