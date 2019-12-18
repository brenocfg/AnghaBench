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
struct ata_channel {int devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_ATAPI_MASTER ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

int
ata_atapi(device_t dev, int target)
{
    struct ata_channel *ch = device_get_softc(dev);

    return (ch->devices & (ATA_ATAPI_MASTER << target));
}