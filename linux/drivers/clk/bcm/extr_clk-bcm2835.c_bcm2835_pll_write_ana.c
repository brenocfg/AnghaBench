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
typedef  scalar_t__ u32 ;
struct bcm2835_cprman {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cprman_write (struct bcm2835_cprman*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
bcm2835_pll_write_ana(struct bcm2835_cprman *cprman, u32 ana_reg_base, u32 *ana)
{
	int i;

	/*
	 * ANA register setup is done as a series of writes to
	 * ANA3-ANA0, in that order.  This lets us write all 4
	 * registers as a single cycle of the serdes interface (taking
	 * 100 xosc clocks), whereas if we were to update ana0, 1, and
	 * 3 individually through their partial-write registers, each
	 * would be their own serdes cycle.
	 */
	for (i = 3; i >= 0; i--)
		cprman_write(cprman, ana_reg_base + i * 4, ana[i]);
}