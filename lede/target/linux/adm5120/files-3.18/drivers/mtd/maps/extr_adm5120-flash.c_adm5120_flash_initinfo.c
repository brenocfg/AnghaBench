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
typedef  size_t u32 ;
struct TYPE_4__ {struct adm5120_flash_platform_data* platform_data; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct map_info {int bankwidth; scalar_t__ phys; int /*<<< orphan*/  set_vpp; int /*<<< orphan*/  copy_from; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
struct flash_desc {size_t srs_shift; scalar_t__ phys; } ;
struct adm5120_flash_platform_data {scalar_t__ window_size; int /*<<< orphan*/  switch_bank; int /*<<< orphan*/  set_vpp; } ;
struct TYPE_3__ {scalar_t__ window_size; int /*<<< orphan*/  switch_bank; struct map_info map; } ;
struct adm5120_flash_info {TYPE_1__ amap; struct platform_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_SIZE_MAX ; 
 int ENODEV ; 
 int /*<<< orphan*/  MAP_ERR (struct map_info*,char*) ; 
 int /*<<< orphan*/  MAP_INFO (struct map_info*,char*,unsigned long,unsigned long,int) ; 
 size_t MEMCTRL_SRS_MASK ; 
 size_t MPMC_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC0 ; 
 int /*<<< orphan*/  SC1 ; 
 size_t SC_MW_MASK ; 
 int /*<<< orphan*/  SWITCH_REG_MEMCTRL ; 
 size_t SW_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm5120_flash_copy_from ; 
 int /*<<< orphan*/  adm5120_flash_read ; 
 int /*<<< orphan*/  adm5120_flash_write ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int* flash_bankwidths ; 
 struct flash_desc* flash_descs ; 
 scalar_t__* flash_sizes ; 
 int /*<<< orphan*/  simple_map_init (struct map_info*) ; 

__attribute__((used)) static int adm5120_flash_initinfo(struct adm5120_flash_info *info,
		struct platform_device *dev)
{
	struct map_info *map = &info->amap.map;
	struct adm5120_flash_platform_data *pdata = dev->dev.platform_data;
	struct flash_desc *fdesc;
	u32 t = 0;

	map->name = dev_name(&dev->dev);

	if (dev->id > 1) {
		MAP_ERR(map, "invalid flash id\n");
		goto err_out;
	}

	fdesc = &flash_descs[dev->id];

	if (pdata)
		info->amap.window_size = pdata->window_size;

	if (info->amap.window_size == 0) {
		/* get memory window size */
		t = SW_READ_REG(SWITCH_REG_MEMCTRL) >> fdesc->srs_shift;
		t &= MEMCTRL_SRS_MASK;
		info->amap.window_size = flash_sizes[t];
	}

	if (info->amap.window_size == 0) {
		MAP_ERR(map, "unable to determine window size\n");
		goto err_out;
	}

	/* get flash bus width */
	switch (dev->id) {
	case 0:
		t = MPMC_READ_REG(SC1) & SC_MW_MASK;
		break;
	case 1:
		t = MPMC_READ_REG(SC0) & SC_MW_MASK;
		break;
	}
	map->bankwidth = flash_bankwidths[t];
	if (map->bankwidth == 0) {
		MAP_ERR(map, "invalid bus width detected\n");
		goto err_out;
	}

	map->phys = fdesc->phys;
	map->size = BANK_SIZE_MAX;

	simple_map_init(map);
	map->read = adm5120_flash_read;
	map->write = adm5120_flash_write;
	map->copy_from = adm5120_flash_copy_from;

	if (pdata) {
		map->set_vpp = pdata->set_vpp;
		info->amap.switch_bank = pdata->switch_bank;
	}

	info->dev = dev;

	MAP_INFO(map, "probing at 0x%lX, size:%ldKiB, width:%d bits\n",
		(unsigned long)map->phys,
		(unsigned long)info->amap.window_size >> 10,
		map->bankwidth*8);

	return 0;

err_out:
	return -ENODEV;
}