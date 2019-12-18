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
struct TYPE_2__ {int max_iosize; int /*<<< orphan*/  setprd; } ;
struct ata_channel {TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_promise_mio_setprd ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_promise_mio_dmainit(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    /* note start and stop are not used here */
    ch->dma.setprd = ata_promise_mio_setprd;
    ch->dma.max_iosize = 65536;
    ata_dmainit(dev);
}