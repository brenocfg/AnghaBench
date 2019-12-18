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
typedef  scalar_t__ u64 ;
struct plt_entry {scalar_t__ add; scalar_t__ br; scalar_t__ adrp; } ;

/* Variables and functions */
 scalar_t__ ALIGN_DOWN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_4K ; 
 scalar_t__ aarch64_insn_adrp_get_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 

bool plt_entries_equal(const struct plt_entry *a, const struct plt_entry *b)
{
	u64 p, q;

	/*
	 * Check whether both entries refer to the same target:
	 * do the cheapest checks first.
	 * If the 'add' or 'br' opcodes are different, then the target
	 * cannot be the same.
	 */
	if (a->add != b->add || a->br != b->br)
		return false;

	p = ALIGN_DOWN((u64)a, SZ_4K);
	q = ALIGN_DOWN((u64)b, SZ_4K);

	/*
	 * If the 'adrp' opcodes are the same then we just need to check
	 * that they refer to the same 4k region.
	 */
	if (a->adrp == b->adrp && p == q)
		return true;

	return (p + aarch64_insn_adrp_get_offset(le32_to_cpu(a->adrp))) ==
	       (q + aarch64_insn_adrp_get_offset(le32_to_cpu(b->adrp)));
}