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
struct dax_device {TYPE_1__* ops; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int (* dax_supported ) (struct dax_device*,struct block_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dax_alive (struct dax_device*) ; 
 int stub1 (struct dax_device*,struct block_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dax_supported(struct dax_device *dax_dev, struct block_device *bdev,
		int blocksize, sector_t start, sector_t len)
{
	if (!dax_alive(dax_dev))
		return false;

	return dax_dev->ops->dax_supported(dax_dev, bdev, blocksize, start, len);
}