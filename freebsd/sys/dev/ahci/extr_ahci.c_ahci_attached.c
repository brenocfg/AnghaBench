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
struct ahci_controller {int /*<<< orphan*/  ch_mtx; struct ahci_channel** ch; } ;
struct ahci_channel {size_t unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
ahci_attached(device_t dev, struct ahci_channel *ch)
{
	struct ahci_controller *ctlr = device_get_softc(dev);

	mtx_lock(&ctlr->ch_mtx);
	ctlr->ch[ch->unit] = ch;
	mtx_unlock(&ctlr->ch_mtx);
}