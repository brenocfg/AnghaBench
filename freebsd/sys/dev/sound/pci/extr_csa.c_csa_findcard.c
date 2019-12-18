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
struct card_type {scalar_t__ devid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct card_type* cards ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct card_type *
csa_findcard(device_t dev)
{
	int i;

	i = 0;
	while (cards[i].devid != 0) {
		if (pci_get_devid(dev) == cards[i].devid)
			return &cards[i];
		i++;
	}
	return NULL;
}