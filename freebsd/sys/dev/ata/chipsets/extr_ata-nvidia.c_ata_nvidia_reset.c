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
struct ata_channel {scalar_t__ devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_sata_phy_reset (int /*<<< orphan*/ ,int,int) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_nvidia_reset(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    if (ata_sata_phy_reset(dev, -1, 1))
	ata_generic_reset(dev);
    else
	ch->devices = 0;
}