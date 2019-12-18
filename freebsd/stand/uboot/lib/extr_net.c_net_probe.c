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
struct netif {int dummy; } ;
struct device_info {scalar_t__ type; } ;
struct TYPE_2__ {int sc_handle; } ;

/* Variables and functions */
 scalar_t__ DEV_TYP_NET ; 
 int devs_no ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct device_info* ub_dev_get (int) ; 
 TYPE_1__ uboot_softc ; 

__attribute__((used)) static int
net_probe(struct netif *nif, void *machdep_hint)
{
	struct device_info *di;
	int i;

	for (i = 0; i < devs_no; i++)
		if ((di = ub_dev_get(i)) != NULL)
			if (di->type == DEV_TYP_NET)
				break;

	if (i == devs_no) {
		printf("net_probe: no network devices found, maybe not"
		    " enumerated yet..?\n");
		return (-1);
	}

#if defined(NETIF_DEBUG)
	printf("net_probe: network device found: %d\n", i);
#endif
	uboot_softc.sc_handle = i;

	return (0);
}