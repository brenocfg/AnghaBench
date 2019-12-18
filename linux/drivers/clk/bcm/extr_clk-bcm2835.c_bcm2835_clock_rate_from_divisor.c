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
typedef  long u64 ;
typedef  int u32 ;
struct bcm2835_clock_data {int int_bits; int frac_bits; } ;
struct bcm2835_clock {struct bcm2835_clock_data* data; } ;

/* Variables and functions */
 int CM_DIV_FRAC_BITS ; 
 int /*<<< orphan*/  do_div (long,int) ; 

__attribute__((used)) static long bcm2835_clock_rate_from_divisor(struct bcm2835_clock *clock,
					    unsigned long parent_rate,
					    u32 div)
{
	const struct bcm2835_clock_data *data = clock->data;
	u64 temp;

	if (data->int_bits == 0 && data->frac_bits == 0)
		return parent_rate;

	/*
	 * The divisor is a 12.12 fixed point field, but only some of
	 * the bits are populated in any given clock.
	 */
	div >>= CM_DIV_FRAC_BITS - data->frac_bits;
	div &= (1 << (data->int_bits + data->frac_bits)) - 1;

	if (div == 0)
		return 0;

	temp = (u64)parent_rate << data->frac_bits;

	do_div(temp, div);

	return temp;
}