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
struct ibv_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 TYPE_1__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 struct ibv_device** ibv_get_device_list (int /*<<< orphan*/ *) ; 
 char* ibv_get_device_name (struct ibv_device*) ; 
 int /*<<< orphan*/  ibv_open_device (struct ibv_device*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int open_device(char *ib_devname)
{
	struct ibv_device **dev_list;
	int i = 0;

	dev_list = ibv_get_device_list(NULL);
	if (!dev_list) {
		fprintf(stderr, "Failed to get IB devices list");
		return -1;
	}

	if (ib_devname) {
		for (; dev_list[i]; ++i) {
			if (!strcmp(ibv_get_device_name(dev_list[i]), ib_devname))
				break;
		}
	}
	if (!dev_list[i]) {
		fprintf(stderr, "IB device %s not found\n",
			ib_devname ? ib_devname : "");
		return -1;
	}

	ctx.context = ibv_open_device(dev_list[i]);
	if (!ctx.context) {
		fprintf(stderr, "Couldn't get context for %s\n",
			ibv_get_device_name(dev_list[i]));
		return -1;
	}

	ibv_free_device_list(dev_list);
	return 0;
}