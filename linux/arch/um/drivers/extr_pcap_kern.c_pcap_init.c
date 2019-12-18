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
struct uml_net_private {scalar_t__ user; } ;
struct pcap_init {int /*<<< orphan*/  filter; int /*<<< orphan*/  optimize; int /*<<< orphan*/  promisc; int /*<<< orphan*/  host_if; } ;
struct pcap_data {int /*<<< orphan*/  host_if; int /*<<< orphan*/  filter; int /*<<< orphan*/  optimize; int /*<<< orphan*/  promisc; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

void pcap_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct pcap_data *ppri;
	struct pcap_init *init = data;

	pri = netdev_priv(dev);
	ppri = (struct pcap_data *) pri->user;
	ppri->host_if = init->host_if;
	ppri->promisc = init->promisc;
	ppri->optimize = init->optimize;
	ppri->filter = init->filter;

	printk("pcap backend, host interface %s\n", ppri->host_if);
}