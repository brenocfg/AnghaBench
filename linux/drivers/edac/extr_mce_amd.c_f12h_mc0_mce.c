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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ LL (int /*<<< orphan*/ ) ; 
 scalar_t__ LL_L1 ; 
 scalar_t__ LL_L2 ; 
 scalar_t__ MEM_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R4_MSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static bool f12h_mc0_mce(u16 ec, u8 xec)
{
	bool ret = false;

	if (MEM_ERROR(ec)) {
		u8 ll = LL(ec);
		ret = true;

		if (ll == LL_L2)
			pr_cont("during L1 linefill from L2.\n");
		else if (ll == LL_L1)
			pr_cont("Data/Tag %s error.\n", R4_MSG(ec));
		else
			ret = false;
	}
	return ret;
}