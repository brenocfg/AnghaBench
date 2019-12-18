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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  pci_restore_state (scalar_t__) ; 

__attribute__((used)) static int
pci_reset_post(device_t dev, device_t child)
{

	if (dev == device_get_parent(child))
		pci_restore_state(child);
	return (0);
}