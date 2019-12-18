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
struct TYPE_2__ {int wps_sec_dev_type_list_len; int /*<<< orphan*/  wps_sec_dev_type_list; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  dev_capab; int /*<<< orphan*/  device_name; } ;
struct p2p_device {TYPE_1__ info; } ;
struct p2p_client_info {int num_sec_dev_types; int /*<<< orphan*/  sec_dev_types; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  dev_capab; int /*<<< orphan*/  dev_name_len; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_copy_filter_devname (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_copy_client_info(struct p2p_device *dev,
				 struct p2p_client_info *cli)
{
	p2p_copy_filter_devname(dev->info.device_name,
				sizeof(dev->info.device_name),
				cli->dev_name, cli->dev_name_len);
	dev->info.dev_capab = cli->dev_capab;
	dev->info.config_methods = cli->config_methods;
	os_memcpy(dev->info.pri_dev_type, cli->pri_dev_type, 8);
	dev->info.wps_sec_dev_type_list_len = 8 * cli->num_sec_dev_types;
	os_memcpy(dev->info.wps_sec_dev_type_list, cli->sec_dev_types,
		  dev->info.wps_sec_dev_type_list_len);
}