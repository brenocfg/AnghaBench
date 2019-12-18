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
struct scoop_dev {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scoop_dev* dev_get_drvdata (struct device*) ; 
 unsigned short ioread16 (scalar_t__) ; 

unsigned short read_scoop_reg(struct device *dev, unsigned short reg)
{
	struct scoop_dev *sdev = dev_get_drvdata(dev);
	return ioread16(sdev->base + reg);
}