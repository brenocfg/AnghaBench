#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct adm5120_flash_platform_data* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct map_info {scalar_t__ size; int bankwidth; scalar_t__ phys; int /*<<< orphan*/  virt; } ;
struct adm5120_flash_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/  parts; } ;
struct TYPE_5__ {scalar_t__ window_size; struct map_info map; } ;
struct adm5120_flash_info {TYPE_2__* mtd; TYPE_1__ amap; int /*<<< orphan*/  res; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAP_ERR (struct map_info*,char*) ; 
 int /*<<< orphan*/  MAP_INFO (struct map_info*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adm5120_flash_initbanks (struct adm5120_flash_info*) ; 
 int adm5120_flash_initinfo (struct adm5120_flash_info*,struct platform_device*) ; 
 int adm5120_flash_initres (struct adm5120_flash_info*) ; 
 int /*<<< orphan*/  adm5120_flash_remove (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 TYPE_2__* do_map_probe (char const*,struct map_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct adm5120_flash_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_device_parse_register (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_types ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct adm5120_flash_info*) ; 
 char** probe_types ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm5120_flash_probe(struct platform_device *dev)
{
	struct adm5120_flash_platform_data *pdata;
	struct adm5120_flash_info *info;
	struct map_info *map;
	const char **probe_type;
	int err;

	pdata = dev->dev.platform_data;
	if (!pdata) {
		dev_err(&dev->dev, "no platform data\n");
		return -EINVAL;
	}

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) {
		err = -ENOMEM;
		goto err_out;
	}

	platform_set_drvdata(dev, info);

	err = adm5120_flash_initinfo(info, dev);
	if (err)
		goto err_out;

	err = adm5120_flash_initres(info);
	if (err)
		goto err_out;

	map = &info->amap.map;
	for (probe_type = probe_types; info->mtd == NULL && *probe_type != NULL;
		probe_type++)
		info->mtd = do_map_probe(*probe_type, map);

	if (info->mtd == NULL) {
		MAP_ERR(map, "map_probe failed\n");
		err = -ENXIO;
		goto err_out;
	}

	adm5120_flash_initbanks(info);

	if (info->mtd->size < info->amap.window_size) {
		/* readjust resources */
		iounmap(map->virt);
		release_resource(info->res);
		kfree(info->res);

		info->amap.window_size = info->mtd->size;
		map->size = info->mtd->size;
		MAP_INFO(map, "reducing map size to %ldKiB\n",
			(unsigned long)map->size >> 10);
		err = adm5120_flash_initres(info);
		if (err)
			goto err_out;
	}

	MAP_INFO(map, "found at 0x%lX, size:%ldKiB, width:%d bits\n",
		(unsigned long)map->phys, (unsigned long)info->mtd->size >> 10,
		map->bankwidth*8);

	info->mtd->owner = THIS_MODULE;

	err = mtd_device_parse_register(info->mtd, parse_types, 0,
				  	pdata->parts, pdata->nr_parts);
	if (err)
		goto err_out;

	return 0;

err_out:
	adm5120_flash_remove(dev);
	return err;
}