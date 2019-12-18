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
typedef  void* u16 ;
struct hd_geometry {void* cylinders; void* sectors; void* heads; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct ace_device {void** cf_id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct ace_device* private_data; } ;

/* Variables and functions */
 size_t ATA_ID_CYLS ; 
 size_t ATA_ID_HEADS ; 
 size_t ATA_ID_SECTORS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ace_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct ace_device *ace = bdev->bd_disk->private_data;
	u16 *cf_id = ace->cf_id;

	dev_dbg(ace->dev, "ace_getgeo()\n");

	geo->heads	= cf_id[ATA_ID_HEADS];
	geo->sectors	= cf_id[ATA_ID_SECTORS];
	geo->cylinders	= cf_id[ATA_ID_CYLS];

	return 0;
}