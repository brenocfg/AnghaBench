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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  LLC_S_FMT ; 
 int /*<<< orphan*/  OR_LLC ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_llc (int /*<<< orphan*/ *) ; 
 struct block* gen_mcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct block *
gen_llc_s(compiler_state_t *cstate)
{
	struct block *b0, *b1;

	/*
	 * Check whether this is an LLC frame.
	 */
	b0 = gen_llc(cstate);

	/*
	 * Now compare the low-order 2 bit of the control byte against
	 * the appropriate value for S frames.
	 */
	b1 = gen_mcmp(cstate, OR_LLC, 2, BPF_B, LLC_S_FMT, 0x03);
	gen_and(b0, b1);
	return b1;
}