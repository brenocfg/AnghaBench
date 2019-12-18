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
struct host_packet {int /*<<< orphan*/  addr; } ;
struct ata_promise_sx4 {int /*<<< orphan*/  mtx; scalar_t__ busy; int /*<<< orphan*/  queue; } ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; struct ata_promise_sx4* chipset_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct host_packet* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct host_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  free (struct host_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ata_promise_next_hpkt(struct ata_pci_controller *ctlr)
{
    struct ata_promise_sx4 *hpktp = ctlr->chipset_data;
    struct host_packet *hp;

    mtx_lock(&hpktp->mtx);
    if ((hp = TAILQ_FIRST(&hpktp->queue))) {
	TAILQ_REMOVE(&hpktp->queue, hp, chain);
	ATA_OUTL(ctlr->r_res2, 0x000c0100, hp->addr);
	free(hp, M_TEMP);
    }
    else
	hpktp->busy = 0;
    mtx_unlock(&hpktp->mtx);
}