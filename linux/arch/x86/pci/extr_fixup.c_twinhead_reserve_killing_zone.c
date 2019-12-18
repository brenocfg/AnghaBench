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
struct pci_dev {int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  request_mem_region (int,int,char*) ; 

__attribute__((used)) static void twinhead_reserve_killing_zone(struct pci_dev *dev)
{
        if (dev->subsystem_vendor == 0x14FF && dev->subsystem_device == 0xA003) {
                pr_info("Reserving memory on Twinhead H12Y\n");
                request_mem_region(0xFFB00000, 0x100000, "twinhead");
        }
}