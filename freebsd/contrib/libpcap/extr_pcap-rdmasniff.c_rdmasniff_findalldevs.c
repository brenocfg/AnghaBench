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
struct ibv_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 struct ibv_device** ibv_get_device_list (int*) ; 

int
rdmasniff_findalldevs(pcap_if_list_t *devlistp, char *err_str)
{
	struct ibv_device **dev_list;
	int numdev;
	int i;
	int ret = 0;

	dev_list = ibv_get_device_list(&numdev);
	if (!dev_list || !numdev) {
		return 0;
	}

	for (i = 0; i < numdev; ++i) {
		/*
		 * XXX - do the notions of "up", "running", or
		 * "connected" apply here?
		 */
		if (!add_dev(devlistp, dev_list[i]->name, 0, "RDMA sniffer", err_str)) {
			ret = -1;
			goto out;
		}
	}

out:
	ibv_free_device_list(dev_list);
	return ret;
}