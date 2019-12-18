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
struct ahci_channel {int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AHCI_MAX_PORTS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

struct ahci_channel *
ahci_getch(device_t dev, int n)
{
	struct ahci_controller *ctlr = device_get_softc(dev);
	struct ahci_channel *ch;

	KASSERT(n >= 0 && n < AHCI_MAX_PORTS, ("Bad channel number %d", n));
	mtx_lock(&ctlr->ch_mtx);
	ch = ctlr->ch[n];
	if (ch != NULL)
		mtx_lock(&ch->mtx);
	mtx_unlock(&ctlr->ch_mtx);
	return (ch);
}