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
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_GET_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_get_id_method(device_t dev, device_t child, enum pci_id_type type,
    uintptr_t *id)
{

	return (PCIB_GET_ID(device_get_parent(dev), child, type, id));
}