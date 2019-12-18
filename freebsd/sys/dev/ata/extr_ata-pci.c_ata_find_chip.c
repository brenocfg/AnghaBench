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
typedef  int uint8_t ;
struct ata_chip_id {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 struct ata_chip_id* ata_match_chip (int /*<<< orphan*/ ,struct ata_chip_id const*) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

const struct ata_chip_id *
ata_find_chip(device_t dev, const struct ata_chip_id *index, int slot)
{
    const struct ata_chip_id *idx;
    device_t *children;
    int nchildren, i;
    uint8_t s;

    if (device_get_children(device_get_parent(dev), &children, &nchildren))
	return (NULL);

    for (i = 0; i < nchildren; i++) {
	s = pci_get_slot(children[i]);
	if ((slot >= 0 && s == slot) || (slot < 0 && s <= -slot)) {
	    idx = ata_match_chip(children[i], index);
	    if (idx != NULL) {
		free(children, M_TEMP);
		return (idx);
	    }
	}
    }
    free(children, M_TEMP);
    return (NULL);
}