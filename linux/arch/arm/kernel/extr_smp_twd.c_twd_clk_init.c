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

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_notifier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ raw_cpu_ptr (scalar_t__) ; 
 int /*<<< orphan*/  twd_clk ; 
 int /*<<< orphan*/  twd_clk_nb ; 
 scalar_t__ twd_evt ; 

__attribute__((used)) static int twd_clk_init(void)
{
	if (twd_evt && raw_cpu_ptr(twd_evt) && !IS_ERR(twd_clk))
		return clk_notifier_register(twd_clk, &twd_clk_nb);

	return 0;
}