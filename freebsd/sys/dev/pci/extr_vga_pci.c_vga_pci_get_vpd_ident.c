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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int pci_get_vpd_ident (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
vga_pci_get_vpd_ident(device_t dev, device_t child, const char **identptr)
{

	return (pci_get_vpd_ident(dev, identptr));
}