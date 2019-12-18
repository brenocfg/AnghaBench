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
struct edd_info {int dummy; } ;
struct edd_device {struct edd_info* info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct edd_info *
edd_dev_get_info(struct edd_device *edev)
{
	return edev->info;
}