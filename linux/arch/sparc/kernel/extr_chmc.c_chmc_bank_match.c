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
struct chmc_bank_info {scalar_t__ valid; unsigned long um; unsigned long uk; unsigned long lm; unsigned long lk; } ;

/* Variables and functions */
 unsigned long PA_LOWER_BITS ; 
 unsigned long PA_LOWER_BITS_SHIFT ; 
 unsigned long PA_UPPER_BITS ; 
 unsigned long PA_UPPER_BITS_SHIFT ; 

__attribute__((used)) static int chmc_bank_match(struct chmc_bank_info *bp, unsigned long phys_addr)
{
	unsigned long upper_bits = (phys_addr & PA_UPPER_BITS) >> PA_UPPER_BITS_SHIFT;
	unsigned long lower_bits = (phys_addr & PA_LOWER_BITS) >> PA_LOWER_BITS_SHIFT;

	/* Bank must be enabled to match. */
	if (bp->valid == 0)
		return 0;

	/* Would BANK match upper bits? */
	upper_bits ^= bp->um;		/* What bits are different? */
	upper_bits  = ~upper_bits;	/* Invert. */
	upper_bits |= bp->uk;		/* What bits don't matter for matching? */
	upper_bits  = ~upper_bits;	/* Invert. */

	if (upper_bits)
		return 0;

	/* Would BANK match lower bits? */
	lower_bits ^= bp->lm;		/* What bits are different? */
	lower_bits  = ~lower_bits;	/* Invert. */
	lower_bits |= bp->lk;		/* What bits don't matter for matching? */
	lower_bits  = ~lower_bits;	/* Invert. */

	if (lower_bits)
		return 0;

	/* I always knew you'd be the one. */
	return 1;
}