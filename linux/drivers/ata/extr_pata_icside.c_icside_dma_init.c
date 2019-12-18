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
struct pata_icside_state {scalar_t__ dma; TYPE_1__* port; } ;
struct pata_icside_info {int /*<<< orphan*/  mwdma_mask; struct expansion_card* ec; struct pata_icside_state* state; } ;
struct expansion_card {scalar_t__ dma; } ;
struct TYPE_2__ {int* speed; } ;

/* Variables and functions */
 int ATA_MAX_DEVICES ; 
 int /*<<< orphan*/  ATA_MWDMA2 ; 
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  request_dma (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icside_dma_init(struct pata_icside_info *info)
{
	struct pata_icside_state *state = info->state;
	struct expansion_card *ec = info->ec;
	int i;

	for (i = 0; i < ATA_MAX_DEVICES; i++) {
		state->port[0].speed[i] = 480;
		state->port[1].speed[i] = 480;
	}

	if (ec->dma != NO_DMA && !request_dma(ec->dma, DRV_NAME)) {
		state->dma = ec->dma;
		info->mwdma_mask = ATA_MWDMA2;
	}

	return 0;
}