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
struct sysc_capabilities {int /*<<< orphan*/  mod_quirks; } ;
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;
struct sysc {struct sysc_capabilities const* cap; TYPE_1__ cfg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sysc_capabilities* of_device_get_match_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_init_match(struct sysc *ddata)
{
	const struct sysc_capabilities *cap;

	cap = of_device_get_match_data(ddata->dev);
	if (!cap)
		return -EINVAL;

	ddata->cap = cap;
	if (ddata->cap)
		ddata->cfg.quirks |= ddata->cap->mod_quirks;

	return 0;
}