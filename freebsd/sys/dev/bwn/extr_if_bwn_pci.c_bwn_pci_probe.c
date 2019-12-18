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
struct bwn_pci_device {int quirks; int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BWN_QUIRK_UNTESTED ; 
 int ENXIO ; 
 int /*<<< orphan*/  attach_untested ; 
 scalar_t__ bwn_pci_find_devcfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bwn_pci_device const**) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_pci_probe(device_t dev)
{
	const struct bwn_pci_device	*ident;

	if (bwn_pci_find_devcfg(dev, NULL, &ident))
		return (ENXIO);

	/* Skip untested devices */
	if (ident->quirks & BWN_QUIRK_UNTESTED && !attach_untested)
		return (ENXIO);

	device_set_desc(dev, ident->desc);
	return (BUS_PROBE_DEFAULT);
}