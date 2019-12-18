#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_channel {TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 size_t ATA_ALTSTAT ; 
 size_t ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 size_t ATA_COUNT ; 
 size_t ATA_ERROR ; 
 size_t ATA_FEATURE ; 
 size_t ATA_IREASON ; 
 size_t ATA_STATUS ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

void
ata_default_registers(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    /* fill in the defaults from whats setup already */
    ch->r_io[ATA_ERROR].res = ch->r_io[ATA_FEATURE].res;
    ch->r_io[ATA_ERROR].offset = ch->r_io[ATA_FEATURE].offset;
    ch->r_io[ATA_IREASON].res = ch->r_io[ATA_COUNT].res;
    ch->r_io[ATA_IREASON].offset = ch->r_io[ATA_COUNT].offset;
    ch->r_io[ATA_STATUS].res = ch->r_io[ATA_COMMAND].res;
    ch->r_io[ATA_STATUS].offset = ch->r_io[ATA_COMMAND].offset;
    ch->r_io[ATA_ALTSTAT].res = ch->r_io[ATA_CONTROL].res;
    ch->r_io[ATA_ALTSTAT].offset = ch->r_io[ATA_CONTROL].offset;
}