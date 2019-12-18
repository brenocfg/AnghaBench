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
struct bcm_clk_hyst {int /*<<< orphan*/  val_bit; int /*<<< orphan*/  en_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_posn_valid (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static bool hyst_valid(struct bcm_clk_hyst *hyst, const char *clock_name)
{
	if (!bit_posn_valid(hyst->en_bit, "hysteresis enable", clock_name))
		return false;

	if (!bit_posn_valid(hyst->val_bit, "hysteresis value", clock_name))
		return false;

	return true;
}