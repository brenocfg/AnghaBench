#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_rdmasniff {unsigned int port_num; struct ibv_device* rdma_device; } ;
struct ibv_device {char const* name; } ;
struct TYPE_4__ {struct pcap_rdmasniff* priv; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 struct ibv_device** ibv_get_device_list (int*) ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  rdmasniff_activate ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 
 unsigned int strtoul (char const*,int /*<<< orphan*/ *,int) ; 

pcap_t *
rdmasniff_create(const char *device, char *ebuf, int *is_ours)
{
	struct pcap_rdmasniff *priv;
	struct ibv_device **dev_list;
	int numdev;
	size_t namelen;
	const char *port;
	unsigned port_num;
	int i;
	pcap_t *p = NULL;

	*is_ours = 0;

	dev_list = ibv_get_device_list(&numdev);
	if (!dev_list || !numdev) {
		return NULL;
	}

	namelen = strlen(device);

	port = strchr(device, ':');
	if (port) {
		port_num = strtoul(port + 1, NULL, 10);
		if (port_num > 0) {
			namelen = port - device;
		} else {
			port_num = 1;
		}
	} else {
		port_num = 1;
	}

	for (i = 0; i < numdev; ++i) {
		if (strlen(dev_list[i]->name) == namelen &&
		    !strncmp(device, dev_list[i]->name, namelen)) {
			*is_ours = 1;

			p = pcap_create_common(ebuf, sizeof (struct pcap_rdmasniff));
			if (p) {
				p->activate_op = rdmasniff_activate;
				priv = p->priv;
				priv->rdma_device = dev_list[i];
				priv->port_num = port_num;
			}
			break;
		}
	}

	ibv_free_device_list(dev_list);
	return p;
}