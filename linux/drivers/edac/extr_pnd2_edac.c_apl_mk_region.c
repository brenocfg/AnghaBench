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
struct region {int dummy; } ;
struct b_cr_asym_mem_region0_mchbar {int /*<<< orphan*/  slice0_asym_limit; int /*<<< orphan*/  slice0_asym_base; } ;

/* Variables and functions */
 scalar_t__ APL_ASYMSHIFT ; 
 scalar_t__ GENMASK_ULL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ U64_LSHIFT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mk_region (char*,struct region*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void apl_mk_region(char *name, struct region *rp, void *asym)
{
	struct b_cr_asym_mem_region0_mchbar *a = asym;

	mk_region(name, rp,
			  U64_LSHIFT(a->slice0_asym_base, APL_ASYMSHIFT),
			  U64_LSHIFT(a->slice0_asym_limit, APL_ASYMSHIFT) +
			  GENMASK_ULL(APL_ASYMSHIFT - 1, 0));
}