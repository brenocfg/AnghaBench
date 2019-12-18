#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pcix_command; scalar_t__ pcix_location; } ;
struct TYPE_4__ {TYPE_1__ pcix; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIXR_COMMAND ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_cfg_restore_pcix(device_t dev, struct pci_devinfo *dinfo)
{
	pci_write_config(dev, dinfo->cfg.pcix.pcix_location + PCIXR_COMMAND,
	    dinfo->cfg.pcix.pcix_command,  2);
}