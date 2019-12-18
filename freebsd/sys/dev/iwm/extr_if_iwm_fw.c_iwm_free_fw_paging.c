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
struct iwm_softc {TYPE_1__* fw_paging_db; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; } ;
struct TYPE_3__ {TYPE_2__ fw_paging_block; } ;

/* Variables and functions */
 int IWM_NUM_OF_FW_PAGING_BLOCKS ; 
 int /*<<< orphan*/  iwm_dma_contig_free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
iwm_free_fw_paging(struct iwm_softc *sc)
{
	int i;

	if (sc->fw_paging_db[0].fw_paging_block.vaddr == NULL)
		return;

	for (i = 0; i < IWM_NUM_OF_FW_PAGING_BLOCKS; i++) {
		iwm_dma_contig_free(&sc->fw_paging_db[i].fw_paging_block);
	}

	memset(sc->fw_paging_db, 0, sizeof(sc->fw_paging_db));
}