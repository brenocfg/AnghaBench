#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int quirks; } ;
struct sysc {TYPE_1__ cfg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SYSC_QUIRK_LEGACY_IDLE ; 
 int /*<<< orphan*/  dev_pm_domain_set (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysc_child_pm_domain ; 

__attribute__((used)) static void sysc_legacy_idle_quirk(struct sysc *ddata, struct device *child)
{
	if (ddata->cfg.quirks & SYSC_QUIRK_LEGACY_IDLE)
		dev_pm_domain_set(child, &sysc_child_pm_domain);
}