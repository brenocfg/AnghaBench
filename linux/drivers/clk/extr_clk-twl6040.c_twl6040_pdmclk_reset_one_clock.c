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
typedef  int /*<<< orphan*/  u8 ;
struct twl6040_pdmclk {int /*<<< orphan*/  twl6040; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6040_HPLLRST ; 
 int twl6040_clear_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const) ; 
 int twl6040_set_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int twl6040_pdmclk_reset_one_clock(struct twl6040_pdmclk *pdmclk,
					  unsigned int reg)
{
	const u8 reset_mask = TWL6040_HPLLRST;	/* Same for HPPLL and LPPLL */
	int ret;

	ret = twl6040_set_bits(pdmclk->twl6040, reg, reset_mask);
	if (ret < 0)
		return ret;

	ret = twl6040_clear_bits(pdmclk->twl6040, reg, reset_mask);
	if (ret < 0)
		return ret;

	return 0;
}