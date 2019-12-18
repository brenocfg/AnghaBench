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
struct hd_geometry {int heads; int sectors; int /*<<< orphan*/  cylinders; } ;
struct driver_data {TYPE_2__* pdev; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct driver_data* private_data; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtip_hw_get_capacity (struct driver_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sector_div (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtip_block_getgeo(struct block_device *dev,
				struct hd_geometry *geo)
{
	struct driver_data *dd = dev->bd_disk->private_data;
	sector_t capacity;

	if (!dd)
		return -ENOTTY;

	if (!(mtip_hw_get_capacity(dd, &capacity))) {
		dev_warn(&dd->pdev->dev,
			"Could not get drive capacity.\n");
		return -ENOTTY;
	}

	geo->heads = 224;
	geo->sectors = 56;
	sector_div(capacity, (geo->heads * geo->sectors));
	geo->cylinders = capacity;
	return 0;
}