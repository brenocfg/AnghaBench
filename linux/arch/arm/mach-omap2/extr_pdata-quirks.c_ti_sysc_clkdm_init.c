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
struct ti_sysc_cookie {void* clkdm; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 void* ti_sysc_find_one_clockdomain (struct clk*) ; 

__attribute__((used)) static int ti_sysc_clkdm_init(struct device *dev,
			      struct clk *fck, struct clk *ick,
			      struct ti_sysc_cookie *cookie)
{
	if (!IS_ERR(fck))
		cookie->clkdm = ti_sysc_find_one_clockdomain(fck);
	if (cookie->clkdm)
		return 0;
	if (!IS_ERR(ick))
		cookie->clkdm = ti_sysc_find_one_clockdomain(ick);
	if (cookie->clkdm)
		return 0;

	return -ENODEV;
}