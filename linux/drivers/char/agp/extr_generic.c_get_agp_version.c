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
typedef  int u32 ;
struct agp_bridge_data {int major_version; int minor_version; int /*<<< orphan*/  capndx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AGP_MAJOR_VERSION_SHIFT ; 
 int AGP_MINOR_VERSION_SHIFT ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void get_agp_version(struct agp_bridge_data *bridge)
{
	u32 ncapid;

	/* Exit early if already set by errata workarounds. */
	if (bridge->major_version != 0)
		return;

	pci_read_config_dword(bridge->dev, bridge->capndx, &ncapid);
	bridge->major_version = (ncapid >> AGP_MAJOR_VERSION_SHIFT) & 0xf;
	bridge->minor_version = (ncapid >> AGP_MINOR_VERSION_SHIFT) & 0xf;
}