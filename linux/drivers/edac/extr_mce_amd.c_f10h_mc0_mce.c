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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ LL (int /*<<< orphan*/ ) ; 
 scalar_t__ LL_L1 ; 
 scalar_t__ R4 (int /*<<< orphan*/ ) ; 
 scalar_t__ R4_GEN ; 
 int f12h_mc0_mce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static bool f10h_mc0_mce(u16 ec, u8 xec)
{
	if (R4(ec) == R4_GEN && LL(ec) == LL_L1) {
		pr_cont("during data scrub.\n");
		return true;
	}
	return f12h_mc0_mce(ec, xec);
}