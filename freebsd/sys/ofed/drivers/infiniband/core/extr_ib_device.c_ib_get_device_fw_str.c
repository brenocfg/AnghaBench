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
struct ib_device {int /*<<< orphan*/  (* get_dev_fw_str ) (struct ib_device*,char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ib_device*,char*,size_t) ; 

void ib_get_device_fw_str(struct ib_device *dev, char *str, size_t str_len)
{
	if (dev->get_dev_fw_str)
		dev->get_dev_fw_str(dev, str, str_len);
	else
		str[0] = '\0';
}