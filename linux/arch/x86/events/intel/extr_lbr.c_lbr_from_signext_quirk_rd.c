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
 int LBR_FROM_FLAG_ABORT ; 
 int LBR_FROM_FLAG_IN_TX ; 
 int /*<<< orphan*/  lbr_from_quirk_key ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 lbr_from_signext_quirk_rd(u64 val)
{
	if (static_branch_unlikely(&lbr_from_quirk_key)) {
		/*
		 * Quirk is on when TSX is not enabled. Therefore TSX
		 * flags must be read as OFF.
		 */
		val &= ~(LBR_FROM_FLAG_IN_TX | LBR_FROM_FLAG_ABORT);
	}
	return val;
}