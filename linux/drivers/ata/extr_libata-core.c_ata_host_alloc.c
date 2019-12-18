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
struct device {int dummy; } ;
struct ata_port {int port_no; } ;
struct ata_host {int n_ports; struct ata_port** ports; int /*<<< orphan*/  kref; struct device* dev; int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ata_devres_release ; 
 struct ata_port* ata_port_alloc (struct ata_host*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ata_host*) ; 
 int /*<<< orphan*/  devres_add (struct device*,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_open_group (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_remove_group (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ata_host*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct ata_host* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ata_host *ata_host_alloc(struct device *dev, int max_ports)
{
	struct ata_host *host;
	size_t sz;
	int i;
	void *dr;

	DPRINTK("ENTER\n");

	/* alloc a container for our list of ATA ports (buses) */
	sz = sizeof(struct ata_host) + (max_ports + 1) * sizeof(void *);
	host = kzalloc(sz, GFP_KERNEL);
	if (!host)
		return NULL;

	if (!devres_open_group(dev, NULL, GFP_KERNEL))
		goto err_free;

	dr = devres_alloc(ata_devres_release, 0, GFP_KERNEL);
	if (!dr)
		goto err_out;

	devres_add(dev, dr);
	dev_set_drvdata(dev, host);

	spin_lock_init(&host->lock);
	mutex_init(&host->eh_mutex);
	host->dev = dev;
	host->n_ports = max_ports;
	kref_init(&host->kref);

	/* allocate ports bound to this host */
	for (i = 0; i < max_ports; i++) {
		struct ata_port *ap;

		ap = ata_port_alloc(host);
		if (!ap)
			goto err_out;

		ap->port_no = i;
		host->ports[i] = ap;
	}

	devres_remove_group(dev, NULL);
	return host;

 err_out:
	devres_release_group(dev, NULL);
 err_free:
	kfree(host);
	return NULL;
}