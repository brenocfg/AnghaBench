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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int (* pm_read ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;} ;
struct ata_channel {TYPE_2__* r_io; int /*<<< orphan*/  dev; TYPE_1__ hw; } ;
struct TYPE_4__ {scalar_t__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDX_INL (struct ata_channel*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int
ata_sata_scr_read(struct ata_channel *ch, int port, int reg, uint32_t *val)
{

    if (ch->hw.pm_read != NULL)
	return (ch->hw.pm_read(ch->dev, port, reg, val));
    if (ch->r_io[reg].res) {
	*val = ATA_IDX_INL(ch, reg);
	return (0);
    }
    return (-1);
}