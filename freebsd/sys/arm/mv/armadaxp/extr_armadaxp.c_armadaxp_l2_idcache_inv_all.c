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
 int /*<<< orphan*/  ALL_WAYS ; 
 int /*<<< orphan*/  ARMADAXP_L2_INV_WAY ; 
 int /*<<< orphan*/  write_l2_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
armadaxp_l2_idcache_inv_all(void)
{
	write_l2_cache(ARMADAXP_L2_INV_WAY, ALL_WAYS);
}