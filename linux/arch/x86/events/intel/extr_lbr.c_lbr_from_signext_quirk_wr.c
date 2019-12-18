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
 int LBR_FROM_SIGNEXT_2MSB ; 
 int /*<<< orphan*/  lbr_from_quirk_key ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

inline u64 lbr_from_signext_quirk_wr(u64 val)
{
	if (static_branch_unlikely(&lbr_from_quirk_key)) {
		/*
		 * Sign extend into bits 61:62 while preserving bit 63.
		 *
		 * Quirk is enabled when TSX is disabled. Therefore TSX bits
		 * in val are always OFF and must be changed to be sign
		 * extension bits. Since bits 59:60 are guaranteed to be
		 * part of the sign extension bits, we can just copy them
		 * to 61:62.
		 */
		val |= (LBR_FROM_SIGNEXT_2MSB & val) << 2;
	}
	return val;
}