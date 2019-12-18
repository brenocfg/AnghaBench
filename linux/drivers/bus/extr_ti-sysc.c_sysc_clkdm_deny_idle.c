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
struct ti_sysc_platform_data {int /*<<< orphan*/  (* clkdm_deny_idle ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct sysc {int /*<<< orphan*/  cookie; int /*<<< orphan*/  dev; scalar_t__ legacy_mode; } ;

/* Variables and functions */
 struct ti_sysc_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sysc_clkdm_deny_idle(struct sysc *ddata)
{
	struct ti_sysc_platform_data *pdata;

	if (ddata->legacy_mode)
		return;

	pdata = dev_get_platdata(ddata->dev);
	if (pdata && pdata->clkdm_deny_idle)
		pdata->clkdm_deny_idle(ddata->dev, &ddata->cookie);
}