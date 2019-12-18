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
typedef  int u64 ;
struct ps3flash_private {int tag; } ;
struct ps3_storage_device {int /*<<< orphan*/  sbd; } ;

/* Variables and functions */
 struct ps3flash_private* ps3_system_bus_get_drvdata (int /*<<< orphan*/ *) ; 
 int ps3flash_read_write_sectors (struct ps3_storage_device*,int,int /*<<< orphan*/ ) ; 
 int ps3flash_writeback (struct ps3_storage_device*) ; 

__attribute__((used)) static int ps3flash_fetch(struct ps3_storage_device *dev, u64 start_sector)
{
	struct ps3flash_private *priv = ps3_system_bus_get_drvdata(&dev->sbd);
	int res;

	if (start_sector == priv->tag)
		return 0;

	res = ps3flash_writeback(dev);
	if (res)
		return res;

	priv->tag = -1;

	res = ps3flash_read_write_sectors(dev, start_sector, 0);
	if (res)
		return res;

	priv->tag = start_sector;
	return 0;
}