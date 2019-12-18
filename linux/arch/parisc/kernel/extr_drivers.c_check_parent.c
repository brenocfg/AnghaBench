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
struct parse_tree_data {struct device* dev; int /*<<< orphan*/  modpath; int /*<<< orphan*/  index; } ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 scalar_t__ check_dev (struct device*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 scalar_t__ match_parisc_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ match_pci_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parisc_bus_type ; 
 struct device* parse_tree_node (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_parent(struct device * dev, void * data)
{
	struct parse_tree_data * d = data;

	if (check_dev(dev)) {
		if (dev->bus == &parisc_bus_type) {
			if (match_parisc_device(dev, d->index, d->modpath))
				d->dev = dev;
		} else if (dev_is_pci(dev)) {
			if (match_pci_device(dev, d->index, d->modpath))
				d->dev = dev;
		} else if (dev->bus == NULL) {
			/* we are on a bus bridge */
			struct device *new = parse_tree_node(dev, d->index, d->modpath);
			if (new)
				d->dev = new;
		}
	}
	return d->dev != NULL;
}