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
struct bitfield {size_t max_bits; int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 

void bitfield_set(struct bitfield *bf, size_t bit)
{
	if (bit >= bf->max_bits)
		return;
	bf->bits[bit / 8] |= BIT(bit % 8);
}