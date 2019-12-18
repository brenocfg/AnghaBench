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
struct TYPE_2__ {int /*<<< orphan*/ * pm_write; int /*<<< orphan*/ * pm_read; int /*<<< orphan*/  tf_write; int /*<<< orphan*/  tf_read; int /*<<< orphan*/  command; int /*<<< orphan*/ * softreset; int /*<<< orphan*/  status; int /*<<< orphan*/  end_transaction; int /*<<< orphan*/  begin_transaction; } ;
struct ata_channel {TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_begin_transaction ; 
 int /*<<< orphan*/  ata_end_transaction ; 
 int /*<<< orphan*/  ata_generic_command ; 
 int /*<<< orphan*/  ata_generic_status ; 
 int /*<<< orphan*/  ata_tf_read ; 
 int /*<<< orphan*/  ata_tf_write ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

void
ata_generic_hw(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    ch->hw.begin_transaction = ata_begin_transaction;
    ch->hw.end_transaction = ata_end_transaction;
    ch->hw.status = ata_generic_status;
    ch->hw.softreset = NULL;
    ch->hw.command = ata_generic_command;
    ch->hw.tf_read = ata_tf_read;
    ch->hw.tf_write = ata_tf_write;
    ch->hw.pm_read = NULL;
    ch->hw.pm_write = NULL;
}