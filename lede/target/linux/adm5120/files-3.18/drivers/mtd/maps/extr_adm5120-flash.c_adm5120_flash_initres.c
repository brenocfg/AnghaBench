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
struct map_info {int /*<<< orphan*/ * virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  window_size; struct map_info map; } ;
struct adm5120_flash_info {TYPE_1__ amap; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAP_ERR (struct map_info*,char*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm5120_flash_initres(struct adm5120_flash_info *info)
{
	struct map_info *map = &info->amap.map;
	int err = 0;

	info->res = request_mem_region(map->phys, info->amap.window_size,
			map->name);
	if (info->res == NULL) {
		MAP_ERR(map, "could not reserve memory region\n");
		err = -ENOMEM;
		goto out;
	}

	map->virt = ioremap_nocache(map->phys, info->amap.window_size);
	if (map->virt == NULL) {
		MAP_ERR(map, "failed to ioremap flash region\n");
		err = -ENOMEM;
		goto out;
	}

out:
	return err;
}