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
struct ti_sysc_cookie {scalar_t__ clkdm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clkdm_deny_idle (scalar_t__) ; 

__attribute__((used)) static void ti_sysc_clkdm_deny_idle(struct device *dev,
				    const struct ti_sysc_cookie *cookie)
{
	if (cookie->clkdm)
		clkdm_deny_idle(cookie->clkdm);
}