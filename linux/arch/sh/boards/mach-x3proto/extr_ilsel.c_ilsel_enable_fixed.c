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
typedef  int /*<<< orphan*/  ilsel_source_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __ilsel_enable (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ilsel_level_map ; 
 unsigned int ilsel_offset (unsigned int) ; 
 scalar_t__ test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 

int ilsel_enable_fixed(ilsel_source_t set, unsigned int level)
{
	unsigned int bit = ilsel_offset(level - 1);

	if (test_and_set_bit(bit, &ilsel_level_map))
		return -EBUSY;

	__ilsel_enable(set, bit);

	return bit;
}