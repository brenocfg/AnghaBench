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
struct ibv_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 int /*<<< orphan*/  ibv_get_device_guid (struct ibv_device*) ; 
 struct ibv_device** ibv_get_device_list (int*) ; 
 char* ibv_get_device_name (struct ibv_device*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

int main(int argc, char *argv[])
{
	struct ibv_device **dev_list;
	int num_devices, i;

	dev_list = ibv_get_device_list(&num_devices);
	if (!dev_list) {
		perror("Failed to get IB devices list");
		return 1;
	}

	printf("    %-16s\t   node GUID\n", "device");
	printf("    %-16s\t----------------\n", "------");

	for (i = 0; i < num_devices; ++i) {
		printf("    %-16s\t%016llx\n",
		       ibv_get_device_name(dev_list[i]),
		       (unsigned long long) be64toh(ibv_get_device_guid(dev_list[i])));
	}

	ibv_free_device_list(dev_list);

	return 0;
}