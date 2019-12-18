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
struct TYPE_2__ {scalar_t__ num_default_heads; } ;
struct edd_info {TYPE_1__ params; } ;
struct edd_device {int dummy; } ;

/* Variables and functions */
 struct edd_info* edd_dev_get_info (struct edd_device*) ; 

__attribute__((used)) static int
edd_has_default_heads(struct edd_device *edev)
{
	struct edd_info *info;
	if (!edev)
		return 0;
	info = edd_dev_get_info(edev);
	if (!info)
		return 0;
	return info->params.num_default_heads > 0;
}