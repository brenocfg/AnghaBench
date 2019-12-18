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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_core_info {int unit; int /*<<< orphan*/  core_idx; int /*<<< orphan*/  hwrev; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct bcma_erom_core {int /*<<< orphan*/  rev; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */

__attribute__((used)) static void
bcma_erom_to_core_info(const struct bcma_erom_core *core, u_int core_idx,
    int core_unit, struct bhnd_core_info *info)
{
	info->vendor = core->vendor;
	info->device = core->device;
	info->hwrev = core->rev;
	info->core_idx = core_idx;
	info->unit = core_unit;
}