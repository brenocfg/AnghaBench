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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  power; } ;

/* Variables and functions */
 int /*<<< orphan*/  nullb_device_bool_attr_show (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* to_nullb_device (struct config_item*) ; 

__attribute__((used)) static ssize_t nullb_device_power_show(struct config_item *item, char *page)
{
	return nullb_device_bool_attr_show(to_nullb_device(item)->power, page);
}