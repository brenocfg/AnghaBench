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
struct clk_si570 {unsigned long rfreq; int /*<<< orphan*/  regmap; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI570_CNTRL_FREEZE_M ; 
 int /*<<< orphan*/  SI570_REG_CONTROL ; 
 unsigned long div64_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si570_update_rfreq (struct clk_si570*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int si570_set_frequency_small(struct clk_si570 *data,
				     unsigned long frequency)
{
	/*
	 * This is a re-implementation of DIV_ROUND_CLOSEST
	 * using the div64_u64 function lieu of letting the compiler
	 * insert EABI calls
	 */
	data->rfreq = div64_u64((data->rfreq * frequency) +
			div_u64(data->frequency, 2), data->frequency);
	regmap_write(data->regmap, SI570_REG_CONTROL, SI570_CNTRL_FREEZE_M);
	si570_update_rfreq(data);
	regmap_write(data->regmap, SI570_REG_CONTROL, 0);

	/* Applying a new frequency (small change) can take up to 100us */
	usleep_range(100, 200);

	return 0;
}