#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * virt; } ;
struct TYPE_4__ {TYPE_1__ map; } ;
struct adm5120_flash_info {int /*<<< orphan*/ * res; TYPE_2__ amap; int /*<<< orphan*/ * mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct adm5120_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm5120_flash_remove(struct platform_device *dev)
{
	struct adm5120_flash_info *info;

	info = platform_get_drvdata(dev);
	if (info == NULL)
		return 0;

	platform_set_drvdata(dev, NULL);

	if (info->mtd != NULL) {
		mtd_device_unregister(info->mtd);
		map_destroy(info->mtd);
	}

	if (info->amap.map.virt != NULL)
		iounmap(info->amap.map.virt);

	if (info->res != NULL) {
		release_resource(info->res);
		kfree(info->res);
	}

	return 0;
}