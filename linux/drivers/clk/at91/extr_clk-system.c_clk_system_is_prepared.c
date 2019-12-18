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
struct clk_system {int id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_SCSR ; 
 int /*<<< orphan*/  AT91_PMC_SR ; 
 int /*<<< orphan*/  is_pck (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_system* to_clk_system (struct clk_hw*) ; 

__attribute__((used)) static int clk_system_is_prepared(struct clk_hw *hw)
{
	struct clk_system *sys = to_clk_system(hw);
	unsigned int status;

	regmap_read(sys->regmap, AT91_PMC_SCSR, &status);

	if (!(status & (1 << sys->id)))
		return 0;

	if (!is_pck(sys->id))
		return 1;

	regmap_read(sys->regmap, AT91_PMC_SR, &status);

	return status & (1 << sys->id) ? 1 : 0;
}