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

/* Variables and functions */
 int /*<<< orphan*/  analyze_64bit_constant (unsigned long,unsigned long,int*,int*,int*) ; 

__attribute__((used)) static bool const64_is_2insns(unsigned long high_bits,
			      unsigned long low_bits)
{
	int highest_bit_set, lowest_bit_set, all_bits_between_are_set;

	if (high_bits == 0 || high_bits == 0xffffffff)
		return true;

	analyze_64bit_constant(high_bits, low_bits,
			       &highest_bit_set, &lowest_bit_set,
			       &all_bits_between_are_set);

	if ((highest_bit_set == 63 || lowest_bit_set == 0) &&
	    all_bits_between_are_set != 0)
		return true;

	if (highest_bit_set - lowest_bit_set < 21)
		return true;

	return false;
}