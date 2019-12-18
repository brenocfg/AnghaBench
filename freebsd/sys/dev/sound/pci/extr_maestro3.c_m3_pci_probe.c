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
struct m3_card_type {scalar_t__ pci_id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int /*<<< orphan*/  CALL ; 
 int ENXIO ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct m3_card_type* m3_card_types ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_pci_probe(device_t dev)
{
	struct m3_card_type *card;

	M3_DEBUG(CALL, ("m3_pci_probe(0x%x)\n", pci_get_devid(dev)));

	for (card = m3_card_types ; card->pci_id ; card++) {
		if (pci_get_devid(dev) == card->pci_id) {
			device_set_desc(dev, card->name);
			return BUS_PROBE_DEFAULT;
		}
	}
	return ENXIO;
}