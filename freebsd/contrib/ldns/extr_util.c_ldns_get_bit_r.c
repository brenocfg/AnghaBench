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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

int
ldns_get_bit_r(uint8_t bits[], size_t index)
{
	/*
	 * The bits are counted from right to left, so bit #0 is the
	 * right most bit.
	 */
	return (int) bits[index / 8] & (1 << (index % 8));
}