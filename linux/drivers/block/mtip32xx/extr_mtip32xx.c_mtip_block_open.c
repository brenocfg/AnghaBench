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
struct driver_data {int /*<<< orphan*/  dd_flag; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVAL_BIT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_block_open(struct block_device *dev, fmode_t mode)
{
	struct driver_data *dd;

	if (dev && dev->bd_disk) {
		dd = (struct driver_data *) dev->bd_disk->private_data;

		if (dd) {
			if (test_bit(MTIP_DDF_REMOVAL_BIT,
							&dd->dd_flag)) {
				return -ENODEV;
			}
			return 0;
		}
	}
	return -ENODEV;
}