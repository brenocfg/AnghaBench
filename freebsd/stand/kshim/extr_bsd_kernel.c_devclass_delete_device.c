#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module_data {TYPE_1__** devclass_pp; } ;
typedef  TYPE_2__* device_t ;
struct TYPE_5__ {size_t dev_unit; int /*<<< orphan*/ * dev_module; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** dev_list; } ;

/* Variables and functions */

__attribute__((used)) static void
devclass_delete_device(const struct module_data *mod, device_t dev)
{
	if (mod == NULL) {
		return;
	}
	mod->devclass_pp[0]->dev_list[dev->dev_unit] = NULL;
	dev->dev_module = NULL;
}