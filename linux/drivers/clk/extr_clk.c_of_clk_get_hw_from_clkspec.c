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
struct of_phandle_args {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct clk_hw *
of_clk_get_hw_from_clkspec(struct of_phandle_args *clkspec)
{
	return ERR_PTR(-ENOENT);
}