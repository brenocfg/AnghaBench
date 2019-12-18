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
struct pata_icside_state {int /*<<< orphan*/  dma; } ;
struct ata_queued_cmd {struct ata_port* ap; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct pata_icside_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_dma_pause (struct ata_port*) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pata_icside_bmdma_stop(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct pata_icside_state *state = ap->host->private_data;

	disable_dma(state->dma);

	/* see ata_bmdma_stop */
	ata_sff_dma_pause(ap);
}