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
typedef  int u32 ;
struct tegra_dfll {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ DFLL_CLOSED_LOOP ; 
 int DFLL_OUTPUT_FORCE_ENABLE ; 
 int EINVAL ; 
 unsigned int OUT_MASK ; 
 int /*<<< orphan*/  dfll_set_force_output_enabled (struct tegra_dfll*,int) ; 
 int dfll_set_force_output_value (struct tegra_dfll*,unsigned int) ; 

__attribute__((used)) static int dfll_force_output(struct tegra_dfll *td, unsigned int out_sel)
{
	u32 val;

	if (out_sel > OUT_MASK)
		return -EINVAL;

	val = dfll_set_force_output_value(td, out_sel);
	if ((td->mode < DFLL_CLOSED_LOOP) &&
	    !(val & DFLL_OUTPUT_FORCE_ENABLE)) {
		dfll_set_force_output_enabled(td, true);
	}

	return 0;
}