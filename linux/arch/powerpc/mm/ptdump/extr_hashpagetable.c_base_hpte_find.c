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
 int /*<<< orphan*/  CONFIG_PPC_PSERIES ; 
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int native_find (unsigned long,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pseries_find (unsigned long,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int base_hpte_find(unsigned long ea, int psize, bool primary, u64 *v,
			  u64 *r)
{
	if (IS_ENABLED(CONFIG_PPC_PSERIES) && firmware_has_feature(FW_FEATURE_LPAR))
		return pseries_find(ea, psize, primary, v, r);

	return native_find(ea, psize, primary, v, r);
}