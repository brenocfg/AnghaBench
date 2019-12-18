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
struct clk_pllv1 {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IMX_PLLV1_IMX21 ; 

__attribute__((used)) static inline bool is_imx21_pllv1(struct clk_pllv1 *pll)
{
	return pll->type == IMX_PLLV1_IMX21;
}