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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  CPU_NEVADA 128 
 int /*<<< orphan*/  GET_CONTEXT (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_ADDU (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_LW (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  build_adjust_context (int /*<<< orphan*/ **,unsigned int) ; 
 int current_cpu_type () ; 

void build_get_ptep(u32 **p, unsigned int tmp, unsigned int ptr)
{
	/*
	 * Bug workaround for the Nevada. It seems as if under certain
	 * circumstances the move from cp0_context might produce a
	 * bogus result when the mfc0 instruction and its consumer are
	 * in a different cacheline or a load instruction, probably any
	 * memory reference, is between them.
	 */
	switch (current_cpu_type()) {
	case CPU_NEVADA:
		UASM_i_LW(p, ptr, 0, ptr);
		GET_CONTEXT(p, tmp); /* get context reg */
		break;

	default:
		GET_CONTEXT(p, tmp); /* get context reg */
		UASM_i_LW(p, ptr, 0, ptr);
		break;
	}

	build_adjust_context(p, tmp);
	UASM_i_ADDU(p, ptr, ptr, tmp); /* add in offset */
}